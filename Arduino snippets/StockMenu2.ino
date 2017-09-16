//This menu uses PIN4 as an interrupt to start the menu, then the other 3 pins to nav
// Saved by Simulator for Arduino V0.97B
// Saved by Simulator for Arduino V0.97B
// IF delay(200) is removed from button() then lcd unreadable!!!??
#include <LiquidCrystal.h>
//#include <PinChangeInt.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define PIN1 8  //Up button
#define PIN2 9  //Down button
#define PIN3 10  //Black button on lunchbox
#define PIN4 11  //Red button

byte menuButton = 0;
boolean menuOn = false;
byte whichButton = 0;
byte pinPressed;
//byte interrupt_count[20]={0}; // 20 possible arduino pins
int count = 0;
void setup() {
  pinMode(PIN1, INPUT); 
  pinMode(PIN2, INPUT); 
  pinMode(PIN3, INPUT); 
  pinMode(PIN4, INPUT); // 1 pin on interrupt, toggles menu on/off 
  //PCintPort::attachInterrupt(PIN4, &quicfunc, FALLING); //disabled for sim
  Serial.begin(9600);
  lcd.begin(16, 2);
 }


void loop() {
                    //button();
 
 switch(menuButton){
case 0:
    lcd.clear();
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

//*****************************   Functions  *********************
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
Serial.println(menuOn);
Serial.println(count = count+1);
}

 
//------------------------------  start menu1  ---------------
void menu1(){

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SET:"); 
    lcd.setCursor(0, 1);
    lcd.print("menu1");
  //lcd.setCursor(0, 1);lcd.blink();
  
  whichButton = button();
switch(whichButton){   // what to do if button pressed
  case 0:
  break;
case 1:  // Up button
            whichButton = 0;
            menuButton = 3;      
  break; 
case 2:  // Down
          whichButton = 0;
          menuButton = 2;       
   break;
   }
}
//==========================  End menu1   ======================
//--------------------------  Start menu2   -------------------
void menu2(){
   
  lcd.clear();lcd.setCursor(0, 0);lcd.print("SET:"); 
  lcd.setCursor(0, 1);lcd.print("menu2");
  //lcd.setCursor(0, 1);lcd.blink();

  whichButton = button();
switch(whichButton){   
case 0:
  break;
case 1:  // Up button
      whichButton = 0;
      menuButton = 1;
  break; 
case 2:  // Down
      whichButton = 0;
      menuButton = 3;
   break;
  }
}
//==========================  End menu2  ===============================
//--------------------------  Start menu3   -------------------
void menu3(){
  
  lcd.clear();lcd.setCursor(0, 0);lcd.print("SET:"); 
  lcd.setCursor(0, 1);lcd.print("menu3");
  //lcd.setCursor(0, 0);lcd.blink();
 
   whichButton = button();      
switch(whichButton){
case 0:
  break;
case 1:  // Up button
      whichButton = 0;
      menuButton = 2;
  break; 
case 2:  // Down
      whichButton = 0;
      menuButton =1;
   break;
  }
}
//==========================  End menu3  ===============================*/
//----------------------------- start of button()  ------------
 int button(){  //(see which button's been pressed and debouncing code)
   
   byte pinState1 = digitalRead(PIN1);
   byte pinState2 = digitalRead(PIN2);
   byte pinState3 = digitalRead(PIN3);
   byte pinPressed1, pinPressed2, pinPressed3; 
   byte result = 0;
   int counter1 = 0;
   int counter2 = 0;
   int counter3 = 0;
   int reading1, reading2, reading3;
   int debounce = 100;
   long time1 = 0;
   long time2 = 0;
   long time3 = 0;

if(millis() != time1){
  reading1 = digitalRead(8); 
    if(reading1 == pinState1 && counter1>0){
      counter1--;
      if(reading1 != pinState1){
        counter1++;}
 if(counter1 >= debounce){
   counter1 = 0;
   pinPressed1 = reading1;
 }
 time1 = millis();
    }
}

if(millis() != time2){
  reading2 = digitalRead(9); 
    if(reading2 == pinState2 && counter2>0){
      counter2--;
      if(reading2 != pinState2){
        counter2++;}
 if(counter2 >= debounce){
   counter2 = 0;
   pinPressed2 = reading2;
 }
 time2 = millis();
    }
}

if(millis() != time3){
  reading3 = digitalRead(10); 
    if(reading3 == pinState3 && counter3>0){
      counter3--;
      if(reading3 != pinState3){
        counter3++;}
 if(counter3 >= debounce){
   counter3 = 0;
   pinPressed3 = reading3;
 }
 time3 = millis();
    }
}

if(reading1 > 0){result = 1;}
if(reading2 == 1){result = 2;}
if(reading3 == 1){result = 3;}
delay(200); 
 return result;
 }
//=================================  end button  =============================


