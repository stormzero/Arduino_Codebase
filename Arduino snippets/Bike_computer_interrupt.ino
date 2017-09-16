  // Kosme Rebel 2012
// Saved by Simulator for Arduino V0.93
//const int RS = 13; //B5
//const int Enable = 12; //B4
//const int D4 = 11; //B3
//const int D5 = 10; //B2
//const int D6 = 9; //B1
//const int D7 = 8; //B0
const int contrast = 6; //D6
const int btnUp = 4; //D4
const int btnDown = 3; //D3
const int btnBack = 5; //D5
const int btnEnter = 7; //D7
const int sensor = 2; //D2
const int cols = 20;
const int rows = 4;
const int distCol = 12;
const int distRow = 3;
const int speedCol = 12;
const int speedRow = 1;
const int timeCol = 12;
const int timeRow = 2;
const int optRun = 0;
const int optConfig = 0;
const int debounceDelay = 10;
const int address = 0;
const int addrContrast = 1;
const float perimeters[] PROGMEM = {
  0.79796, 0.87776, 0.95756, 1.03735, 1.11715, 1.19695, 1.27674, 1.35654, 1.43634, 
  1.51613, 1.59593, 1.67573, 1.75552, 1.83532, 1.91511, 1.99491, 2.07471, 2.1545, 
  2.2343, 2.3141
};

byte battMeter[][8] = {
  {0x0E, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F}, //0
  {0x0E, 0x1F, 0x11, 0x11, 0x11, 0x13, 0x17, 0x1F}, //1
  {0x0E, 0x1F, 0x11, 0x11, 0x13, 0x17, 0x1F, 0x1F}, //2
  {0x0E, 0x1F, 0x11, 0x13, 0x17, 0x1F, 0x1F, 0x1F}, //3
  {0x0E, 0x1F, 0x13, 0x17, 0x1F, 0x1F, 0x1F, 0x1F}, //4
  {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}  //5
};

typedef enum STATES{ INIT, STOP, RUN, PAUSE, CONFIG } states_t;

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "boards.h"

//LiquidCrystal lcd(RS,Enable,D4,D5,D6,D7);
LiquidCrystal lcd(12,11,10,9,8,7);

int mins = 0;
int secs = 0;
int hrs = 0;
int decs = 0;
int index = 0;
unsigned long duration = 0;
volatile unsigned long speedTime = 0;
float Speed = 0;
float perim = 0;
volatile float distance = 0;
char buffer[25];
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
  for(int i=0;i<6;i++)
    lcd.createChar(i,battMeter[i]);
  index = EEPROM.read(address);
  if(index>19)
  {
    index=0;
    EEPROM.write(address,index);
  }
  perim = pgm_read_float(&perimeters[index]);
  lcd.clear();
  analogWrite(contrast,EEPROM.read(addrContrast));
  attachInterrupt(0,turn,FALLING);
}

void loop()
{
  switch(state)
  {
    case INIT:
      //show chingaderas
      boolean up;
      boolean down;
      boolean back;
      boolean enter;
      int tmp;
      tmp = 0;
      lcd.print("Bike Computer");
      lcd.setCursor(0,1);
      lcd.print("Version 1.2");
      state = STOP;
    break;
    
    case STOP:
      enter = debounce(btnEnter);
      up = debounce(btnUp);
      down = debounce(btnDown);
      if(enter)
      {
        delay(2000);
        enter = debounce(btnEnter);
        {
          distance = 0;
          duration = millis();
          speedTime = millis();
          state = RUN;
          break;
        }
      }
      if (up||down)
      {
        tmp = index;
        state=CONFIG;
      }
    break;
    
    case RUN:
      enter = debounce(btnEnter);
      back = debounce(btnBack);
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
        updateTime();
      }
      updateDistance();
      if(enter)
      {
        state = PAUSE;
        break;
      }
      if(back)
      {
        delay(2000);
        back = debounce(btnBack);
        if(back)
          state=STOP;
      }
    break;
    
    case PAUSE:
      enter = debounce(btnEnter);
      if(enter)
      {
        duration=millis();
        state = RUN;
      }
    break;
    
    case CONFIG:
      enter = debounce(btnEnter);
      up = debounce(btnUp);
      down = debounce(btnDown);
      back = debounce(btnBack);
      lcd.clear();
      lcd.print("Wheel diam: ");
      if((tmp>20)||(tmp<1))
        lcd.print("ERR");
      else
        lcd.print(tmp+9);
      if(up)
      {
        tmp++;
        if(tmp>20)
          tmp = 1;
      }
      if(down)
      {
        tmp--;
        if(tmp<1)
          tmp = 20;
      }
      if(enter)
      {
        if(tmp!=index)
        {
          EEPROM.write(address,tmp);
          perim = pgm_read_float(&perimeters[index]);
          index = tmp;
        }
        state = STOP;
      }
      if(back)
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

void updateTime()
{
  char temp[8];
  String time = "";
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
  if(hrs==0)
  {
    temp[0] = ' ';
    temp[1] = ' ';
    //time.concat("  ");
  } 
  else
  {
    temp[0] = hrs;
    temp[1] = ':';
    //time.concat(hrs);
    //time.concat(':');
  }
  if(mins<10)
  {
    //time.concat('0');
    temp[2] = '0';
  }
  else
  {
    temp[2] = mins / 10;
  }
  temp[3] = mins % 10;
  //time.concat(mins);
  temp[4] = ':';
  //time.concat(':');
  if(secs<10)
  {
    //time.concat('0');
    temp[5] = '0';
  }
  else
  {
    temp[5] = secs / 10;
  }
  temp[6] = secs % 10;
  //temp[7] = null;
  //time.concat(secs);
  lcd.setCursor(timeCol,timeRow);
  //lcd.print(time);
  lcd.print(temp);
}

void updateDistance()
{
  boolean change = false;
  lcd.setCursor(distCol,distRow);
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

void turn()
{
  if(state == RUN)
  {
    lcd.setCursor(speedCol,speedRow);
    lcd.print(dtostrf((perim*3600)/(millis()-speedTime),3,2,buffer));
    speedTime = millis();
    lcd.print(" km/h");
    lcd.print("   ");
    distance += perim;
  }
}

long senseBattery() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

