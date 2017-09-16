
// Saved by Simulator for Arduino V0.97.B.2
 #include <LiquidCrystal.h>
 LiquidCrystal lcd(10, 9, 5, 4, 3, 2); // -- creating LCD instance

 unsigned long currentTime;
 unsigned long loopTime;
 const int pin_A = 6;  // pin 12
 const int pin_B = 7;  // pin 11
 const int pin_P = 8;  // pin 11 druktoets
 unsigned char encoder_A;
 unsigned char encoder_B;
 unsigned char encoder_P;
 unsigned char encoder_A_prev=0;

 //char* menu[]={"Temperatuur","Temp min max"};
 char* menu[5];
 int moduulherkenning=0;
 int x=0;
 int druk=0;
 int m=0;
 int keuze;
 void setup()  {
  
  float sensorBAT = analogRead(A3);
  float sensorBATVOLT= 0.71+10*(sensorBAT/1024); //diode drop 0.7 Volt
  int moduulherkenning=0;
  int lcdNumCols = 16; // -- number of columns in the LCD
  float Vratio = 0;
  float SWR = 0;
  
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  pinMode(pin_P, INPUT);
  
  currentTime = millis();
  loopTime = currentTime; 
  
  lcd.begin(lcdNumCols,2);
  lcd.clear();
  lcd.setCursor (3, 0);
  lcd.print ("VERON A48");
  lcd.setCursor (1, 1);
  lcd.print ("Zelfbouw 2012");
  delay(2000);
  lcd.setCursor (0, 1);
  lcd.print ("               ");
  lcd.setCursor (1, 1);
  lcd.print ("Bat ");
  lcd.setCursor (6, 1);
  lcd.print(sensorBATVOLT,1);
  lcd.setCursor (10, 1);
  lcd.print("Volt");
  delay(4000);
  lcd.clear();

// moduulherkenning 
  int keuze=analogRead(A0);
  if (keuze< 15 && keuze>5)
    {
     
    }
  if (keuze< 25 && keuze>15)
    {
      menu[0]="Temperatuur";
      menu[1]="Temp min max";
      printTemp();
    } 
    
  lcd.setCursor (5, 1);
    lcd.print ("(DRUK)");
  
} 

void loop()  {
  // get the current elapsed time
  
  currentTime = millis();
  if(currentTime >= (loopTime + 5)){
    // 5ms since last check of encoder = 200Hz  
    encoder_A = digitalRead(pin_A);    // Read encoder pins
    encoder_B = digitalRead(pin_B);   
    encoder_P = digitalRead(pin_P);   
    
    if((!encoder_A) && (encoder_A_prev)&&(druk==1)){
    //if((!encoder_A) && (encoder_A_prev)){ 
      // A has gone from high to low 
      if(encoder_B) 
      {
        x++;
        if ((x>2)&&(druk==1)){x=1;}
        {  
          lcd.setCursor(1,0);  
            lcd.print ("                ");  
          lcd.setCursor(1,0);  
            lcd.print (menu[x-1]);  
          lcd.setCursor (1, 1);
             lcd.print ("(draai/druk)");
        }
        delay(100);
        // B is high so clockwise            
      }   
      else
      {
        x--;
        if ((x< 1)&&(druk==1)){x=2;}
        {  
          lcd.setCursor(1,0);  
            lcd.print ("                ");  
          lcd.setCursor(1,0);  
            lcd.print (menu[x-1]);  
          lcd.setCursor (1, 1);
             lcd.print ("(draai/druk)");
        }
      
        delay(100);
        // B is low so counter-clockwise                 
      }   
    }   
    encoder_A_prev = encoder_A;     // Store value of A for next time    
    loopTime = currentTime;  // Updates loopTime
      
  }
  // Other processing can be done here
  if (!encoder_P) // check op drukschakelaar
          {
            druk++;
            lcd.clear();
            if(druk==1)
              {
                x=1;
                lcd.setCursor(1,0);  
                   lcd.print ("                ");  
                lcd.setCursor(1,0);  
                  lcd.print (menu[x-1]);
                lcd.setCursor (1, 1);
                  lcd.print ("(draai/druk)");
              }
            else
              { 
                lcd.setCursor (0, 1);
                lcd.print("                ");// wissen van regel2
               }
            if (druk>1){druk=0;}
            delay(500);
          }  
       
         // Other processing can be done here   
         
 if ((druk==0)&&(x!=0))
 {
 switch (x)
  {
    case 1: m=0;printTemp();
    break;
    case 2: m=1;printTemp();
    break;
    default:{lcd.setCursor (1, 0);lcd.print ("Bestaat niet");}
   delay(1000); 
  }
 }       
        
        
        
}

void Menu_1()
{
  lcd.clear();
  lcd.setCursor (1, 0);
    lcd.print (menu[0]);
  lcd.setCursor (10, 0);
     lcd.print ("(DRUK)");
  int i=0;
  while (digitalRead(pin_P)==1)
    {
      i++;
      lcd.setCursor (1, 1);
        lcd.print (i);
      delay(100);
     } 
}

 void Menu_2()
{
  lcd.clear();
  lcd.setCursor (1, 0);
    lcd.print (menu[1]);
  lcd.setCursor (10, 0);
            lcd.print ("(DRUK)");
  int i=0;
  while (digitalRead(pin_P)==1)
    {
      i--;
      lcd.setCursor (1, 1);
        lcd.print (i);
      delay(100);
     }
}

// hieronder staan de functies die afhankelijk van de modullherkenning worden aangesproken
// --------------------------------- TEMPERATUUR METING ---------------------------
void printTemp(void) {
  float fTemp;
  float tempg=0;
  float temp=0;
  float max=0;
  float min=100;

  while (digitalRead(pin_P)==1)
 {
  tempg=0;
  for (int i=0; i< 5; i++)
    {
    tempg=tempg+Thermister(analogRead(A4));
     temp=0.7+tempg/(i+1);// correctie op temperatuur
    delay(100);
    }
    
    if(temp>max){max=temp;}
    if(temp<min){min=temp;}
  
  lcd.setCursor(1,0);
  lcd.print("Temp ");
  lcd.setCursor(7,0);
  lcd.print(temp,1);
  lcd.setCursor(12,0);
  lcd.print(" ");
  lcd.print(char(223));
  lcd.print("C");
    if(m==1)
    {  
      lcd.setCursor(0,1);
      lcd.print("Mx ");
      lcd.print(max,1);
      lcd.setCursor(9,1);
      lcd.print("Mn ");
      lcd.print(min,1);
     }
 
 }
 }


 float Thermister(int RawADC) 
 {
  float Temp;
  // See http://en.wikipedia.org/wiki/Thermistor for explanation of formula
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // Convert Kelvin to Celcius
  return Temp;
}

