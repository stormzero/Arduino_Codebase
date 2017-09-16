const int cols = 20;
// Saved by Simulator for Arduino V0.96.A.2
// Saved by Simulator for Arduino V0.96.A.2
const int rows = 4;
const int distCol = 12;
const int distRow = 2;
const int speedCol = 12;
const int speedRow = 1;
const int timeCol = 0;
const int timeRow = 2;
const int btnUp = 8; //B0
const int btnDown = 9; //B1
const int btnBack = 11; //B3
const int btnEnter = 10; //B2
const int sensor = 12; //B4
const int optRun = 0;
const int optConfig = 0;
const int debounceDelay = 10;
const int address = 0;

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <stdlib.h>

//LiquidCrystal lcd(RS,Enable,D4,D5,D6,D7);
LiquidCrystal lcd(2,3,4,5,6,7);

int mins = 0;
int secs = 0;
int hrs = 0;
int decs = 0;
int pos = 0;
boolean up;
boolean down;
boolean back;
boolean enter;
boolean sense;
int tmp = 0;
unsigned long duration = 0;
unsigned long speedTime = 0;
float Speed = 0;
float perim = 0;
float distance = 0;
char buffer[25];

void setup()
{
  pinMode(btnUp,INPUT);
  digitalWrite(btnUp,HIGH);
  pinMode(btnDown,INPUT);
  digitalWrite(btnDown,HIGH);
  pinMode(btnBack,INPUT);
  digitalWrite(btnBack,HIGH);
  pinMode(btnEnter,INPUT);
  digitalWrite(btnEnter,HIGH);
  pinMode(sensor,INPUT);
  digitalWrite(sensor,HIGH);
  lcd.begin(cols,rows);
  pos = EEPROM.read(address);
  perim = loadPerim();
  lcd.clear();
}

void loop()
{
  enter = debounce(btnEnter);
  back = debounce(btnBack);
  sense = debounce(sensor);
  if(millis()- duration > 1000)
  {
     duration = millis();
     secs++;
     if(secs >59)
     {
       secs=0;
       mins++;
     }
     if(mins>59)
     {
       mins=0;
       hrs++;
     }
     printTime();
   }
   if(sense)
   {
     Speed = (perim*3600)/(millis()-speedTime);
     speedTime = millis();
     updateSpeed();
     distance += perim;
     updateDistance();
   }
}

float loadPerim()
{
  switch(pos)
  {
    case 1://10
    return 0.798;
    break;
    case 2://11
    return 0.878;
    break;
    case 3://12
    return 0.958;
    break;
    case 4://13
    return 1.037;
    break;
    case 5://14
    return 1.117;
    break;
    case 6://15
    return 1.197;
    break;
    case 7://16
    return 1.277;
    break;
    case 8://17
    return 1.357;
    break;
    case 9://18
    return 1.436;
    break;
    case 10://19
    return 1.516;
    break;
    case 11://20
    return 1.596;
    break;
    case 12://21
    return 1.676;
    break;
    case 13://22
    return 1.756;
    break;
    case 14://23
    return 1.835;
    break;
    case 15://24
    return 1.915;
    break;
    case 16://25
    return 1.995;
    break;
    case 17://26
    return 2.075;
    break;
    case 18://27
    return 2.155;
    break;
    case 19://28
    return 2.234;
    break;
    case 20://29
    return 2.314;
    break;
    default:
    return 0;
    break;
  }
  return ((pos+9)*0.254*0.314159);
}

boolean debounce(int pin)
{
  boolean state;
  boolean previousState = digitalRead(pin);
  for(int counter=0;counter<debounceDelay;counter++)
  {
    delay(1);
    state = digitalRead(pin);
    if(state!=previousState)
    {
      counter = 0;
      previousState = state;
    }
  }
  return !state;
}

void printTime()
{
  lcd.setCursor(timeCol,timeRow);
  //for(int i=timeCol;i<cols;i++)
    //lcd.print(" ");
  lcd.setCursor(timeCol,timeRow);
  if(hrs==0)
    lcd.print("  ");
  else
  {
    lcd.print(hrs);
    lcd.print(":");
  }
  if(mins<10)
    lcd.print('0');
  lcd.print(mins);
  lcd.print(":");
  if(secs<10)
    lcd.print('0');
  lcd.print(secs);
}

void updateSpeed()
{
  char buffer[25];
  lcd.setCursor(speedCol,speedRow);
  lcd.print(dtostrf(Speed,3,2,buffer));
  lcd.print(" km/h");
  lcd.print("   ");
}

void updateDistance()
{
  boolean change = false;
  lcd.setCursor(distCol,distRow);
  //for(int i = distCol;i<cols;i++)
    //lcd.print(' ');
  int decim=0;
  int units=0;
  if(distance>=100)
  {
    decs++;
    distance-=100;
    change = true;
  }
  if(change)
  {
    units = decs / 10;
    decim = decs % 10;
    lcd.setCursor(distCol,distRow);
    if(units<10)
      lcd.print(' ');
    lcd.print(units);
    lcd.print('.');
    lcd.print(decim);
    lcd.print(" km");
  }
}
