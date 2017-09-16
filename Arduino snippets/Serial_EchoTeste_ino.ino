
// Saved by Simulator for Arduino V0.97B
// Saved by Simulator for Arduino V0.97.A.5
// Saved by Simulator for Arduino V0.97.A.5
// Saved by Simulator for Arduino V0.97A
#include <Servo.h>

Servo servo1;   // create servo object to control a servo
 
 char string[21];
        int AA0;
        int AA1;
        int AA2;
        int AA3;
        int AA4;
        int AA5;
        int AA6;
        int AA7;
        int AA8;
        int AA9;
        int len=0;
        int inByte;
 int control; 
 void setup() {
   
     servo1.attach(5);  // attaches the servo on pin 5 to the servo object       
                     
   Serial.begin(9600); //INTIALISING THE SERIAL PORT       
                    }
  

void loop()  // LOOP FUNCTION
{
   inByte = Serial.read();
   
   if (inByte == '!') {len=0;read_serial();}// If Start of line ("!") is found, call read_serial() function     
}
  
 void read_serial()  // FUNCTION FOR READING THE SERIAL MESSAGE
{
    while (inByte!= '*') // As long as EOL not found, keep reading
    {
    if (Serial.available() > 0 ) // if new data is available
    { 
                  inByte = Serial.read(); // Read new byte
           string[len] = inByte; // Save the data in a character array
                 // Serial.print(string[len]);Serial.print(int(string[len]));
                  
                 if (inByte == '*')
                  { Serial.print(len)  ;    Serial.print('+')  ;  
                    AA0=(int)string[0]-35; AA1=(int)(string[1])-35;   AA2=(int)(string[2])-35; AA3=(int)(string[3])-35;   AA4=(int)(string[4])-35; 
                    AA5=(int)(string[5])-35; AA6=(int)(string[6])-35;   AA7=(int)(string[7])-35; AA8=(int)(string[8])-35;   AA9=(int)(string[9])-35;
                    control= AA0+AA1+AA2+AA3+AA4+AA5+AA6+AA7+AA8;
                    control=(control/9);    
                    if (len == 10) 
                      // if (len == 10&& AA9==control)  
                       {   Serial.print(AA0);Serial.print('-');Serial.print(AA1);Serial.print('-');Serial.println(AA2);
                         
                           // servo1.write(AA0);                                                  
                            if (AA1>=32){digitalWrite(6, HIGH);AA1=AA1-32;Serial.print(6);Serial.print("-on  ");}else {digitalWrite(6, LOW);Serial.print(6);Serial.print("-off  ");}
                            if (AA1>=16){digitalWrite(7, HIGH);AA1=AA1-16;Serial.print(7);Serial.print("-on  ");}else {digitalWrite(7, LOW);Serial.print(7);Serial.print("-off  ");}
                            if (AA1>=8){digitalWrite(8, HIGH);AA1=AA1-8;Serial.print(8);Serial.print("-on  ");}else {digitalWrite(8, LOW);Serial.print(8);Serial.print("-off  ");}
                            if (AA1>=4){digitalWrite(9, HIGH);AA1=AA1-4;Serial.print(9);Serial.print("-on  ");}else {digitalWrite(9, LOW);Serial.print(9);Serial.print("-off  ");}
                            if (AA1>=2){digitalWrite(10, HIGH);AA1=AA1-2;Serial.print(10);Serial.print("-on  ");}else {digitalWrite(10, LOW);Serial.print(10);Serial.print("-off  ");}
                            if (AA1>=1){digitalWrite(11, HIGH);AA1=AA1-1;Serial.print(11);Serial.println("-on  ");}else {digitalWrite(11, LOW);Serial.print(11);Serial.println("-off  ");}
                            
                            if (AA2>=32){digitalWrite(12, HIGH);AA2=AA2-32;Serial.print(12);Serial.print("-on  ");}else {digitalWrite(12, LOW);Serial.print(12);Serial.print("-off  ");}
                            if (AA2>=16){digitalWrite(13, HIGH);AA2=AA2-16;Serial.print(13);Serial.print("-on  ");}else {digitalWrite(13, LOW);Serial.print(13);Serial.print("-off  ");}
                            if (AA2>=8){digitalWrite(14, HIGH);AA2=AA2-8;Serial.print(14);Serial.print("-on  ");}else {digitalWrite(14, LOW);Serial.print(14);Serial.print("-off  ");}
                            if (AA2>=4){digitalWrite(15, HIGH);AA2=AA2-4;Serial.print(15);Serial.print("-on  ");}else {digitalWrite(15, LOW);Serial.print(15);Serial.print("-off  ");}
                            if (AA2>=2){digitalWrite(16, HIGH);AA2=AA2-2;Serial.print(16);Serial.print("-on  ");}else {digitalWrite(16, LOW);Serial.print(16);Serial.print("-off  ");}
                            if (AA2>=1){digitalWrite(17, HIGH);AA2=AA2-1;Serial.print(17);Serial.println("-on  ");}else {digitalWrite(17, LOW);Serial.print(17);Serial.println("-off  ");}
                            
                        }
                      
                        //Serial.print(len);Serial.print('-');Serial.print(AA1);Serial.print('-');Serial.println(AA2);     
                
               } 
           len=len+1;    
     }  
}
}

