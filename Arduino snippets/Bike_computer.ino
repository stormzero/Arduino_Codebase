const int RS = 2; //D2
// Saved by Simulator for Arduino V0.96.0.2
const int Enable = 3; //D3
const int D4 = 4; //D4
const int D5 = 5; //D5
const int D6 = 6; //D6
const int D7 = 7; //D7
const int cols = 20;
const int rows = 4;
const int timeCol = 12;
const int timeRow = 2;
const int distCol = 12;
const int distRow = 3;
const int btnUp = 8; //B0
const int btnDown = 9; //B1
const int btnBack = 10; //B2
const int btnEnter = 11; //B3
const int sensor = 12; //B4
const int optRun = 0;
const int optConfig = 0;
const int debounceDelay = 10;
const int address = 0;

typedef enum STATES{ INIT, STOP, RUNNING, PAUSE, CONFIG } states_t;

#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(DS,Enable,D4,D5,D6,D7);
//LiquidCrystal lcd(2,3,4,5,6,7);

int mins = 0;
int secs = 0;
int hrs = 0;
int decs = 0;
int pos = 0;
unsigned long duration = 0;
unsigned long ride = 0;
unsigned long perim = 0;
unsigned long distance = 0;
states_t state;

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
  switch(state)
  {
    case INIT:
      //show chingaderas
      int tmp;
      lcd.print("Bike Computer");
      state = STOP;
    break;
    
    case STOP:
      if(debounce(btnEnter))
      {
        distance = 0;
        duration=millis();
        state = RUNNING;
      }
      if((debounce(btnUp))||(debounce(btnDown)))
      {
        tmp = pos;
        state=CONFIG;
      }
    break;
    
    case RUNNING:
      if(millis( )- duration > 1000)
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
      if(debounce(sensor))
      {
        distance += perim;
        updateDistance();
      }
      if(debounce(btnEnter))
      {
        state = PAUSE;
        //pausar chuglio
      }
      if(debounce(btnBack))
      {
        state=STOP;
      }
      
    break;
    
    case PAUSE:
      if(debounce(btnEnter))
      {
        duration=millis();
        state = RUNNING;
      }
    break;
    
    case CONFIG:
      lcd.clear();
      lcd.print("Wheel diam: ");
      if((tmp>20)||(tmp<1))
        lcd.print("ERR");
      else
        lcd.print(tmp+9);
      if(debounce(btnUp))
      {
        tmp++;
        if(tmp>20)
          tmp = 1;
      }
      if(debounce(btnDown))
      {
        tmp--;
        if(tmp<1)
          tmp = 20;
      }
      if(debounce(btnEnter))
      {
        if(tmp!=pos)
        {
          EEPROM.write(address,tmp);
          perim = loadPerim();
          pos = tmp;
        }
        state = STOP;
      }
      if(debounce(btnBack))
        state = STOP;
    break;
  }
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

void updateDistance()
{
  lcd.setCursor(distCol,distRow);
  //for(int i = distCol;i<cols;i++)
    //lcd.print(' ');
  int decim=0;
  int units=0;
  if(distance/100>decs)
    decs++;
  if(decs>10)
  {
    decim = decs % 10;
    units = decs / 10;
  }
  lcd.setCursor(distCol,distRow);
  if(units<10)
    lcd.print(' ');
  lcd.print(units);
  lcd.print('.');
  lcd.print(decim);
  lcd.print(" km");
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
}
