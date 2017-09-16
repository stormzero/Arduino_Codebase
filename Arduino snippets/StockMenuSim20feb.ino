#include <LiquidCrystal.h>
// Saved by Simulator for Arduino V0.97B
//#include <PinChangeInt.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define PIN1 8  //Up button
#define PIN2 9  //Down button
#define PIN3 10  //Black button on lunchbox
#define PIN4 11  //Red button

int menuButton = 0;
boolean menuOn = true;
byte whichButton = 0;
byte whichButtonOld = 0;
byte pinPressed;
String leadup = "menu(";
String end = ")";
//byte interrupt_count[20]={0}; // 20 possible arduino pins
int count = 0;

void setup() {                                             //##########################  SETUP

  pinMode(PIN1, INPUT);   // Up
  pinMode(PIN2, INPUT);   // Down
  pinMode(PIN3, INPUT);   // Black
  pinMode(PIN4, INPUT);   // Red
  //PCintPort::attachInterrupt(PIN4, &quicfunc, FALLING); //disable for sim  ***
  //Serial.begin(9600);
  lcd.begin(16, 2);
 }
 
void loop() {                                               //###########################  LOOP

button();    // Determines which button was pressed
  // Change this to read if(menuOn == true){button();}   once the menu is toggling on & off from Red pin

loopMenu();  // loops menuButton to read correctly

activateMenu();  // runs activateMenu() function using previous menuButton variable

}

//*****************************   Functions  *********************

 
//------------------------------  start menu1  ---------------
void menu1(){

  lcd.clear();                            // Print to LCD
  lcd.setCursor(0, 0);
  lcd.print("SET:"); 
    lcd.setCursor(0, 1);
    lcd.print("menu1");
//lcd.setCursor(0, 1);lcd.blink();
delay(200);
}

//==========================  End menu1   ======================
//--------------------------  Start menu2   -------------------
void menu2(){
   
  lcd.clear();lcd.setCursor(0, 0);lcd.print("SET:");                             // Print to LCD
  lcd.setCursor(0, 1);lcd.print("menu2");
  //lcd.setCursor(0, 1);lcd.blink();
  delay(200);
 }

//==========================  End menu2  ===============================
//---------------------------------------  Start menu3   -------------------

void menu3(){
  
  lcd.clear();lcd.setCursor(0, 0);lcd.print("SET:");                             // Print to LCD
  lcd.setCursor(0, 1);lcd.print("menu3");
  //lcd.setCursor(0, 0);lcd.blink();
  delay(200);
 }

//=============================  End menu3  ===============================

//-----------------------------------------  start button()  --------------------------------------------

void button(){    //new way of determining whichButton value
whichButtonOld = whichButton;
whichButton = 0;
for(byte i = 8; i <12; i++){                           //Find out which button has been pressed (8 - 11)
if(digitalRead(i) ==1){whichButton = i;}     //Store pin # in whichButton
} 

}

//============================  end button()  ============================

//----------------------------------------  start loopMenu()  ---------------------------------------

void loopMenu(){
if(whichButton != whichButtonOld){
switch(whichButton){        // Adjust menuButton to correct reading according to whichButton
case 0:
 break;
case 8:
  switch(menuButton){
  case 0: menuButton = 1; break;
  case 1: menuButton = 2; break;
  case 2: menuButton = 3; break;
  case 3: menuButton = 1; break;
 break;
case 9:
   switch(menuButton){
  case 0: menuButton = 1; break;
  case 1: menuButton = 3; break;
  case 2: menuButton = 1; break;
  case 3: menuButton = 2; break;

break;
 case 10:
break;
 }
}
}
}}

//============================  end loopMenu()  =================================

//-----------------------------------------  start activateMenu  ------------------------------------------

void activateMenu(){
switch(menuButton){   // Now what to do once menuButton has been set
case 0:
break;
case 1:
 menu1();
break;
case 2:
 menu2();
break;
case 3:
 menu3();
break;
}
}

//============================  end activateMenu  =================================



/*  disable for sim***
//------------------------------------------  start qicfunc  --------------------------------------------------

void quicfunc() {
  byte prepinPressed=PCintPort::arduinoPin;
  //interrupt_count[pinPressed]++;
  delay(20);
  byte postpinPressed=PCintPort::arduinoPin;
  if(prepinPressed == postpinPressed){
  menuOn = !menuOn;
  if(menuOn == true){  menuButton = 1; }  // pin 4 (interrupt has been pressed, starts menu on menu1 
  else{menuButton = 0;}
  }
  delay(200);
Serial.println(menuOn);
Serial.println(count = count+1);
}

//============================  end quicfunc =====================  */
