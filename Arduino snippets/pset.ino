/*
// Saved by Simulator for Arduino V0.98.A.2
by Holger Weigert
 version 1.0
 
 
 
 Editor     : Holger Weigert
 Date       : 08.11.2012
 
 * Update the library and sketch to compatible with IDE V1.0 and earlier
 
 */

#include "LCD4884.h"
#include "DFrobot_bmp.h"
int i=0;
int zaehler = 0;
char string[10];
int a=0;
int reihe=1;
int x1=0;
int y1=0;
int abzug=0;
int spalte=0;
int by=0;
int y2=0;
int b=1;
int ss=0;
 int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
 
void setup()
{
 
  lcd.LCD_init();
  lcd.LCD_clear();
  lcd.backlight(OFF);
  //String st =" ";
  int  adc_key_val[5] ={
  50, 200, 400, 600, 800 };
  //Serial.begin(9600);          //  setup serial
} 

void loop()
{
if (ss==0){lcd.backlight(OFF);}
if (ss==1){lcd.backlight(ON);}

  // test
 

   y1=1;
  
   for (x1=0;x1<84;x1++)
   {pset();}
  
 // test ende
 
 
  //line();

 val = analogRead(analogPin);    // read the input pin
  //Serial.println(val);             // debug value
lcd.LCD_set_XY(255,1); 


lcd.LCD_write_string(0,3,"Joystick" ,0);
//String st ="a"; 
// String st =  String(analogRead(A0), DEC); 

//itoa(counter,string,10);
itoa(val,string,10);
lcd.LCD_write_string(1,4,"    ",0);
lcd.LCD_write_string(1,4,string,0);
lcd.LCD_write_string(0,2,"mitte=LichtI/0",0);
//Serial.println(val);
if (val < 750 and val >730)
{
  lcd.LCD_write_string(1,5,"Oben ",0);
  
}

if (val == 327)
{
  lcd.LCD_write_string(1,5,"unten",0);
}
if (val <10)
{
  lcd.LCD_write_string(1,5,"links",0);
}
if (val >140 and val <150)
{
 lcd.LCD_write_string(1,5,"mitte ",0);
 if (ss==0){
 ss=1;}
  else
  {
 ss=0;
delay(500);
}
if (val >490 and val <520)
{
  lcd.LCD_write_string(1,5,"rechts",0);
}
if (val >1000)
{
  lcd.LCD_write_string(1,5,"      ",0);
}

//lcd.LCD_write_string(1,1,st ,0);
  
 
}
}


void charmap()
{
  char i,j;
  for(i=0; i<5; i++){
    for(j=0; j<14; j++){
      lcd.LCD_set_XY(j*6,i);
      lcd.LCD_write_char(i*14+j+32, MENU_NORMAL);
    }
}
}

void line()
{

  for (i = 0; i < 83; i++)   
        {   
            lcd.LCD_set_XY(i, a); 
            lcd.LCD_write_byte(254, 1); 
            
        }
        if (a<6)
                {
          a=a+1;
        }
}
        
void pset()

{
  reihe=1;
  if (y1 <8)
  {
    reihe=0;
    abzug=0;
  }
  if (y1 <16 and y1>7)
  {
    reihe=1;
    abzug=8;
  }
  if (y1 <24 and y1>15)
  {
    reihe=2;
    abzug=16;
  }
   if (y1 <32 and y1>23)
   {
     reihe=3;
     abzug=24;
   }
   if (y1 <40 and y1>31)
   {
     reihe=4;
     abzug=32;
   }
   if (y1 >39)
   {
     reihe=5;
     abzug=40;
   }
   if (x1<7)
   {
     spalte=0;
   }
   if (x1<12 and x1>6)
   {
     spalte=1;
   }
   if (x1<18 and x1>11)
   {
     spalte=2;
   }
   if (x1<24 and x1>17)
   {
     spalte=3;
   }
   if (x1<30 and x1>23)
   {
     spalte=4;
   }
   if (x1<36 and x1>29)
   {
     spalte=5;
   }
   if (x1<42 and x1>35)
   {
     spalte=6;
   }
   if (x1<48 and x1>41)
   {
     spalte=7;
   }
   if (x1<54 and x1>47)
   {
     spalte=8;
   }
   if (x1<60 and x1>53)
   {
     spalte=9;
   }
   if (x1<66 and x1>59)
   {
     spalte=10;
   }
   if (x1<72 and x1>65)
   {
     spalte=11;
   }
   if (x1<78 and x1>71)
   {
     spalte=12;
   }
   if (x1<84 and x1>77)
   {
     spalte=13;
   }
   // reihe=Zeile 0-5
   // abzug = abzug an punkten
   lcd.LCD_set_XY(x1, reihe); 
   y1=y1-abzug;
   if (y1=0)
   {y2=1;}//00000001
   if (y1=1)
   {y2=2;}//00000010
    if (y1=2)
   {y2=4;}//00000100
    if (y1=3)
   {y2=8;}//00001000
    if (y1=4)
   {y2=16;}//00010000
    if (y1=5)
   {y2=32;}//00100000
    if (y1=6)
   {y2=64;}//01000000
    if (y1=7)
   {y2=128;}//10000000
   
   lcd.LCD_write_byte(random(255), 1);
     //Serial.println(x1); 
//Serial.println(reihe);     
}
        
        







