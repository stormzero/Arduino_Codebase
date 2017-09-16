
/*
Converts 8 bit Binary word to Decimal & Hex.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * Switches:- bit 0 to bit 5 connected to A0 to A5
 * bit 6 to digital pin 8
 * bit 7 to digital pin 9
 * Second connection on all switches to Ground.
 * Internal pullup resistors are 
 * activated on all input pins.

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5,4,3,2);

void setup() {
 
 // Set switch input pins & pullups.
 int b0a=A0;
 int b1a=A1;
 int b2a=A2;
 int b3a=A3; 
 
 int b0=A0;int b1=A1;int b2=A2;int b3=A3;int 
b4=A4;
   int b5=A5;int b6=8;int b7=9;
     pinMode(A0,INPUT_PULLUP);pinMode(A1,INPUT_PULLUP);
pinMode(A2,INPUT_PULLUP);pinMode(A3,INPUT_PULLUP);
pinMode(A4,INPUT_PULLUP);pinMode(A5,INPUT_PULLUP);
pinMode(8,INPUT_PULLUP);pinMode(9,INPUT_PULLUP);
digitalWrite(A0,HIGH);digitalWrite(A1,HIGH);
digitalWrite(A2,HIGH);digitalWrite(A3,HIGH);
digitalWrite(A4,HIGH);digitalWrite(A5,HIGH);
digitalWrite(8,HIGH);digitalWrite(9,HIGH);


  lcd.begin(16, 2);
  // Print a message to the LCD.
   lcd.print("Dec=");
 
}

   void loop() {
 int hexL=0;int hexH=0;
 
int dec=0;
    int b0=A0;int b1=A1;int b2=A2;int b3=A3;int
    b4=A4; int b5=A5;int b6=8;int b7=9;
    
    //Get binary word
    
b0=digitalRead(A0);b1=digitalRead(A1);b2=digitalRead(A2);b3=digitalRead(A3);
b4=digitalRead(A4);b5=digitalRead(A5);b6=digitalRead(8);b7=digitalRead(9);
 int bit0=0;int bit1=0;int bit2=0;int bit3=0;int
 bit4=0;int bit5=0;int bit6=0;int bit7=0;
 
  
  
  
  // Display binary word
  
 lcd.setCursor(0,1);
 lcd.print("Bin=");
 lcd.print(b7);lcd.print(b6);lcd.print(b5);lcd.print(b4);
 lcd.print(b3);lcd.print(b2);lcd.print(b1);lcd.print(b0);
 
 //Convert bits to decimal
 
 if (b0==1){bit0=1;}
 b0=0;
 if(b1==1){bit1=2;}
 b1=0;
 if(b2==1){
 b2=0;bit2=4;}
 if(b3==1){bit3=8;}
 b3=0;
 if(b4==1){bit4=16;}
 b4=0;
 if(b5==1){bit5=32;}
 b5=0;
 if(b6==1){bit6=64;}
 b6=0;
 if(b7==1){bit7=128;}
 b7=0;
 dec=(bit0+bit1+bit2+bit3+bit4+bit5+bit6+bit7);
 
 //display decimal
 
 lcd.setCursor(4,0);lcd.print(dec);
 
 //Remove previous decimal display
 
 lcd.print("  ");
 
 lcd.setCursor(9,0);lcd.print("HEX=");
 hexH=(bit4+bit5+bit6+bit7);hexH=hexH >> 4;
 if (hexH <10){lcd.print(hexH);};
 if(hexH==10){lcd.print("A");};
 if(hexH==11){lcd.print("B");};if(hexH==12){lcd.print("C");};
 if(hexH==13){lcd.print("D");};if(hexH==14){lcd.print("E");};
 if(hexH==15){lcd.print("F");};
 hexL=(bit0+bit1+bit2+bit3);
 if(hexL <10){lcd.print(hexL);};
 if(hexL==10){lcd.print("A");};
 if(hexL==11){lcd.print("B");};if(hexL==12){lcd.print("C");};
 if(hexL==13){lcd.print("D");};if(hexL==14){lcd.print("E");};
 if(hexL==15){lcd.print("F");};
}


