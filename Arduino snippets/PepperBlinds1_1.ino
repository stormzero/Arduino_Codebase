/*
// Saved by Simulator for Arduino V0.98
Automated Blinds Controller
Original Program by Sarbjeet Singh
Updated by Mark Pepper to fit into a 328 - by removing the temperature feature
Last revision: November, 2012

Ethernet/SD card shield uses the following ports
D11 - MOSI
D12 - MISO
D13 - SCK
D10 - Select W5100
D4 - SD select
A0 - SD write protect
A1 - SD card detect

Motor shieled uses the following ports:
D11 - motor 1/stepper 1
D3 - motor 2/stepper 2
D5 - motor 3/stepper 3
D6 - motor 4/stepper 4
D4-D12* DC/stepper 74HC595 serial to parallel latch

* NOTE that D12 on the shield needs to be redirected to D9 on the Arduino for this project *

D9 - servo 1
D10 - servo 2

The additional port connections used for this project are as follows:
A0 - Temp input voltage
A1 - Luminosity input voltage. LDR from here to +5V, 100R from here to GND

NOTE that the code below has had the temp functions commented out to reduce the project code size.
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Time.h>
#include <AFMotor.h>
#include <SD.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x0D, 0xE0 };
IPAddress ip(192,168,1,110); // Sets the IP address of the Arduino Ethernet card

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
 
byte mem0=0; 
byte mem1=0; //variables to set transition state
byte photocellPin=1; //Input Pin for Photocell
byte stepperRevolution=200; //number of steps taking for stepper to make on revolution. 
byte limitRev=5;//number of revolutions needed to open or close blind. 
byte NumberOfRevsFor=0; //Counter for number of revolutions completed by stepper motor going forward.
byte NumberOfRevsBack=limitRev; //Counter for number of revolutions completed by stepper motor in reverse.
AF_Stepper motor(200,2); //200 step/rev motor connect to M3 and M4 on motor shield 
File myFile; 
String value;
byte SDreadAtStart=0;
byte openHour,closeHour, OvRCtl=0, timeHour, timeMin; 
int Luminosity; //variable which sensor luminosity reading is compared against. 

void setup()
{  
   Serial.begin(9600); 
   pinMode(10, OUTPUT); //set up reading and writing to SD card
   SD.begin(4);    
   motor.setSpeed(50); //set motor 200 rpm.
   // start the Ethernet connection and the server:
   Ethernet.begin(mac, ip);    
   server.begin();  
   delay(1000); //Give ethernet and sensors time to set up.   
}

//*****************************************************************************
//This is the main loop that calls the other routines
void loop()   
{    
  byte SDread;   
  SDread=EthernetClients();   //checks to see if client is connected  
  
// The following section only runs once when the Arduino is reset. 
// It reads a time from the SD card and starts the Arduino time with it.
  if(SDreadAtStart==0||SDread==1)
  {            
      //reads values from Settings.txt
   SDreader("BlindCtl/Settings/Settings.txt"); 
      setTime(timeHour,timeMin,0,10,7,2012);  
      SDreadAtStart=1;     
  }      
  //Serial.println(Luminosity);           
    motors(Luminosity,openHour,closeHour); // Call the Motors routine
}

//*****************************************************************************
//This routine performs the bulk of the program's functions
void motors(int luminosity, byte openHour, byte closeHour)
{
 // Serial.println(F("motors is started"));
  time_t t=now();//set current time to variable t
  byte curTime=hour(t); //saves the current hour
  Serial.println(curTime); 
  delay(10); //delay to let voltage settle before reading from photocell
  analogRead(photocellPin);
  delay(10);
  int photocellReading=analogRead(photocellPin);//reads the photocell value
  delay(10);
  //checks for variable that indicates if blinds should auto open and then 
  //sets requirements to low. 
  if(OvRCtl==1)
  {
    luminosity=200; 
    openHour=0;
    closeHour=24; 
  }
  //checks variable to see if override for close is enables and then sets 
  //requirements high.
  else if(OvRCtl==2) 
  {
    luminosity=999; 
    openHour=0;
    closeHour=24;    
  }
  else
  {
    //error checks to make sure user has not entered values outside of scope.
 if(luminosity<=200||luminosity>=1000)
      luminosity=600; 
    if(openHour<=(-1)||openHour>=25)
      openHour=13;
   if(closeHour<=(-1)||closeHour>=25)
      closeHour=20;
  } 
  
  if(mem0==0&&mem1==0)//State one where blinds are closed
  { 
   // Serial.print("Blinds are closed \n");
   //If all three of these conidtions are met, blinds will move into opening 
   //state. 
   if((photocellReading>=luminosity)&&(curTime>=openHour)&&(curTime<closeHour))
    { 
      mem0=1;
    }
  }
  
  else if(mem0==1&&mem1==0)//Moving forward state
  { 
    //Serial.print("Blinds are opening \n");    
 //checks to see if blinds are fully open and if so, switches to fully 
 //open state.
    if(NumberOfRevsFor==limitRev)  
    {          
     mem1=1;
     mem0=1; 
    }  
 //confirms that opening condition is still present and continues to move 
 //motor forward 
     else if((photocellReading>=luminosity)&&(curTime>=openHour)&&(curTime<closeHour)) 
    {
      motor.step(stepperRevolution, FORWARD, DOUBLE); 
      motor.release();
      NumberOfRevsFor++;      
      NumberOfRevsBack--;
    } 
 //switches state to move back in closing condition has become true
    else if(curTime>=closeHour||photocellReading<luminosity)
    {      
      mem1=1;
      mem0=0; 
    }     
      
  }
  
  else if(mem0==1&&mem1==1)//Full Open position
  {
   // Serial.print("Blinds are open \n");
   //condition to move into closing state
    if(curTime>=closeHour||photocellReading<luminosity)
    {
      mem1=1;
      mem0=0; 
    }    
  }
  
  else if(mem0==0&&mem1==1)//Blinds closing state
  {  
   //Serial.print("Blinds are closing \n"); 
   //switches to closed state if blinds are fully closed.
    if(NumberOfRevsBack==limitRev) 
    {
     mem1=0;
     mem0=0; 
    }   
 //checks for closing conditions and then proceeds to close blinds.
    else if(curTime>=closeHour||photocellReading<luminosity) 
    {
      motor.step(stepperRevolution, BACKWARD, DOUBLE);
      motor.release(); 
      NumberOfRevsBack++;
      NumberOfRevsFor--;
    } 
 //if conditions for blinds opening become true, switches to blind open 
 //state
    else if(photocellReading>=luminosity&&curTime>=openHour&&curTime<closeHour)
    {       
      mem1=0;
      mem0=1; 
    }
  }
  Serial.print(mem0);
  Serial.print(mem1);
  return; 
}
//*****************************************************************************
//web clients that takes what the user sets and saves them to teh SD card
byte EthernetClients()
{
  boolean stopreading=0,variablePresent=0,storevalue=0,timeOn=0;
  boolean clientC=0, equalsCount=0, SDread=0;
  String readURL;
  
  delay(10); 
  EthernetClient client = server.available(); 
  //Serial.println("Eth");  
  if (client) 
  {    
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    //Serial.println("Client available"); 
    Serial.println(F("Client")); 
    
    while (client.connected()) 
 {
      if (client.available()) 
   {
       
        char c = client.read();
        if(c=='?')
        {
          variablePresent=1;        
        }        
                
        if (c=='z')
  { //stops reading into the string once end of header is reached. 
          stopreading=1;
  }
  //reads in GET from the HTTP header
        else if(c!='z' && stopreading==0&&variablePresent==1)
        {
          readURL+=c;
        //Serial.println(readURL);        
        }
        
 //reads stored GET header to extract variables
     if(stopreading==1&&variablePresent==1&&storevalue==0)
     { 
       
      for(int i=0; i<=(readURL.length()-1); i++)
      {        
        if(readURL[i]=='=')
        {
          int j=i+1;
          while(readURL[j]!='&'&&readURL[j]!='x')
          {
             value+=readURL[j];
             j++;
          }           
         
         if(value=="Open")
           OvRCtl=1;  
     
         if(value=="Close")
           OvRCtl=2;  
     
         if(equalsCount==0&&value=="Time")
   {
            timeOn=1;
            OvRCtl=0;
   }
         else if(value!="Open"&&value!="Close"&&equalsCount==0)
    {
           SD.remove("BlindCtl/Settings/Settings.txt");
           myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);          
           myFile.print(F("Luminx"));
           myFile.print(value); 
           myFile.print("z");
           myFile.close();   
          }
         if(equalsCount==1)
        {    
          // myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);      
          // myFile.print(F("Tempx"));
          // myFile.print(value); 
          // myFile.print("z");
          // myFile.close(); 
        }  
         if(equalsCount==2)
        {   
          myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);        
          myFile.print(F("OpenHourx"));
          myFile.print(value); 
          myFile.print("z"); 
          myFile.close(); 
        }
        if(equalsCount==3)
        {         
          myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);  
          myFile.print(F("CloseHourx"));
          myFile.print(value); 
          myFile.print("z"); 
          myFile.close();
        } 
        if(equalsCount==4)
        {         
          myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);  
          myFile.print(F("Hourx"));
          myFile.print(value); 
          myFile.print("z"); 
          myFile.close();
        }
        if(equalsCount==5)
        {         
          myFile= SD.open("BlindCtl/Settings/Settings.txt",FILE_WRITE);  
          myFile.print(F("Minx"));
          myFile.print(value); 
          myFile.print("z"); 
          myFile.close();
        }
    equalsCount++;
          value="";                  
       }
      }
      storevalue=1; 
     }     
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
     if (c == '\n' && currentLineIsBlank) 
     {          
       // send a standard http response header
       client.println(F("HTTP/1.1 200 OK"));
       client.println(F("Content-Type: text/html"));
       client.println();         
       //Any variables cannot contain the characters of z or x! Last variable 
    //values must end with xz.
       client.println(F("<div align='center'"));
       client.println(F("<h1>Pepper Blinds Client V 1.1</h1>"));
       client.println(F("</div>"));
       if(timeOn==0)  
       {         
          client.println(F("<form name='input' action='192.168.0.10' method='get'>"));
          client.println(F("<input type='radio' name='action' value='Openxz' /> Open"));
          client.println(F("<input type='radio' name='action' value='Closexz' /> Close"));
          client.println(F("<input type='radio' name='action' value='Timexz' /> Time"));           
          client.println(F("</br>"));
          client.println(F("<input type='submit' value='Submit'/>"));
          client.println(F("</form>"));
       }
       else if(timeOn==1)
       {
          client.println(F("<form name='input' action='192.168.0.10' method='get'>"));            
          client.println(F("Luminosity:<input type='text' name='Hour' value='600'/>"));
          client.println(F("</br>"));            
          client.println(F("Open Blinds At (hour):<input type='text' name='openTime'/>"));
          client.println(F("Close Blinds At (hour):<input type='text' name='closeTime'/>"));
          client.println(F("</br>"));
          client.println(F("Current Hour:<input type='text' name='Hour'/>"));
          client.println(F("Current Min:<input type='text' name='Min'/>"));
          client.println(F("<input type=hidden name='action' value='xz' />"));
          client.println(F("<input type='submit' value='Submit'/>"));            
          client.println(F("</form>"));
          client.println(F("</br>"));                         
        }                     
          
      break;
      }
      if (c == '\n') 
   {
          // you're starting a new line
         currentLineIsBlank = true;
      } 
      else if (c != '\r') 
   {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
      }
    }
      
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    SDread=1; 
    //Serial.print('Broswer is closed'); 
  }
  return SDread; 
}

//*****************************************************************************
//function to read the values from teh SD card into variables
void SDreader(const char* fileName)
{
  byte equalsCount=0;
  String readURL; 
 //Serial.println('SD'); 
  myFile= SD.open(fileName);      

       while(myFile.available())//reads the entire file in a String
      { 
        char c=myFile.read(); 
        readURL+=c; 
      }
      myFile.close();
      //Serial.println(readURL);
   //extracts values from file that are between x and z
      for(int i=0; i<=(readURL.length()); i++)
      {
        
      if(readURL[i]=='x')
       {         
         int j=i+1;
         i=j; 
         while(readURL[j]!='z')
         {
           value+=readURL[j];
           j++;
         }            
       //Serial.println(value);
       if(equalsCount==0)
          {
            char string_as_char[value.length()+1];
            value.toCharArray(string_as_char,value.length()+1);         
            Luminosity=atoi(string_as_char);
            //Serial.println(Luminosity);            
          }
          if(equalsCount==1)
          {
            //char string_as_char[value.length()+1];
            //value.toCharArray(string_as_char,value.length()+1);         
            //Luminosity=atoi(string_as_char);
            //Serial.println(Luminosity);            
          }
           if(equalsCount==2)
          {
            char string_as_char[value.length()+1];
            value.toCharArray(string_as_char,value.length()+1);         
            openHour=atoi(string_as_char);
            //Serial.println(Luminosity);            
          }
          
          if(equalsCount==3)
          {
            char string_as_char[value.length()+1];
            value.toCharArray(string_as_char,value.length()+1);         
            closeHour=atoi(string_as_char);             
          }
          
          if(equalsCount==4)
          {
            char string_as_char[value.length()+1];
            value.toCharArray(string_as_char,value.length()+1);         
            timeHour=atoi(string_as_char);             
          }
          if(equalsCount==5){
            char string_as_char[value.length()+1];
            value.toCharArray(string_as_char,value.length()+1);         
            timeMin=atoi(string_as_char);          
          }          
             
         equalsCount++;
          value="";                  
       }
      }
      //Serial.print(Luminosity);
      return; 
}

