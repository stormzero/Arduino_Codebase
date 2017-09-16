// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
#include <LiquidCrystal.h>
#include <FreqCounter.h>

// Initialize the library with pin nrs of the Arduino
const int cntPin = 5;              // Counts pulses
const int dirPin = 6;              // Up or Down count (direction of Rotary Encoder)
int a;                   // Just a variable
float x;
signed float y;
byte z;
signed int frq;
unsigned int S_data[10];
int n=0;
float F_CNT=80000;
float F_VCO;
float F_LCD;                        // The displayed frequency is 2 x the VCO-frequency!!
float F_LCD_old;
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);     //rs,E,d4,d5,d6,d7

void setup()
{
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);                // Chip Select (CS)
  pinMode(12,OUTPUT);               // Clock
  pinMode(13,OUTPUT);               // Data
  // INITIALIZE THE FIXED VALUES OF THE SYNTHESIZER REGISTERS (CX72392), 18 bit mode (feb. 2013/PCH

  S_data[3]=12288;                     // Data = 0. AUX Divider register
  S_data[4]=16384;                     // Data = 0. AUX Divident register
  S_data[5]=20480;                     // 20480 + 0. Reference Freq Divider register. Ref divider is set to Div/1
  S_data[6]=25616;                     // 24576 + 1040. Control Register Phase Detect, Charge Pump. Phase det gain and Charge Pump both set to "16" 
  S_data[7]=28848;                     // 28672 + 176. Control Register Power Down, Multiplexer Output Select. Data = 0xb0 (176 dec) (AUX are OFF)
  S_data[8]=32768;                     // Modulation Control. Only address is send, data bits are 0x0000
  S_data[9]=36864;                     // Modulation Data. Only address is send, data bits are 0x0000

  n=3;
  //SEND THE DEFAULT AND FIXED REGISTER VALUES TO THE SYNTHESIZER
  while (n<10)
  {
    digitalWrite(7, LOW);                            // Make CS = 0
    shiftOut(13, 12, MSBFIRST, (S_data[n] >> 8));  
    // shift out lowbyte
    shiftOut(13, 12, MSBFIRST, S_data[n]);  
    digitalWrite(7, HIGH);                            // Make CS = 1  
    //****END SENDING DATA****
    n++;
  }

  lcd.begin(20, 2);                  // 2 x 20 character display
  lcd.setCursor(0, 0);              // Cursor on Character 0, line 0
  lcd.print("Synthesizer Program-");
  lcd.setCursor(0, 1);              // Cursor on Character 0, line 1
  lcd.print("mer   PA0EHG    2013");

  delay(2000);                      // Delay of 2000 ms
  lcd.clear();
  FreqCounter::f_comp= 0;             // Set compensation to 0
}

void loop()
{
  // put your main code here, to run repeatedly: 
  FreqCounter::start(100);            // Start counting with gate time of 100ms  
  if (digitalRead(6)==0) (a=-1);        // Sign (direction of rotary encoder, ie: Up or Down count)
  else a=1;

  frq=(frq/2);                      // Om de Rotary Encoder iets minder zenuwachtig te maken. Verhoog desgewenst de deler nog iets

  frq=(frq*a);
  F_CNT=F_CNT+frq;
  if (F_CNT > 120000) (F_CNT=75000);    // Frequency in 100 kHz step resolution
  if (F_CNT < 75000) (F_CNT=120000);
  F_LCD=F_CNT/10;
  F_VCO=F_LCD/2;                       // F_VCOsynthesizer = Output freq/2, as the synthesizer frequency is multiplied by 2 externally.

  lcd.setCursor(0, 0);              // Cursor on Character 0, line 0
  lcd.print("Freq.=");
  if (F_LCD<10000)
  {
    lcd.print(" ");                    // Send counter value to LCD for debug purposes
    lcd.setCursor(7, 0);              // Cursor on Character 0, line 0
    lcd.print(F_LCD);
  }
  else
  {
    lcd.setCursor(6, 0);
    lcd.print(F_LCD);
  }
  lcd.setCursor(14, 0);              // Cursor on Character 0, line 0
  lcd.print("MHz");                    // Send counter value to LCD for debug purposes
  frq=0;

  x=(F_VCO/40);
  S_data[0]=(round(x))-32;
  y=(x-S_data[0])*262144;



y=1235/10;			// JUST AN EXAMPLE. RESULT SHOWS AS 123, NOT 123.5 UNDER "FLOAT
y=round(y);"		// RESULT OF round IS 0



  z=y;                              // Only 8 lower bits are copied into tegister z, which is 1 Byte long
  S_data[2]=z+4096;                 // LSB filled with 8 least significant bits
  S_data[1]=((y>>8)+8192);            // MSB filled with 10 most significant bits

  if (F_LCD!=F_LCD_old)
  {
    n=0;
    while (n<3)
    {
      //SEND SERIAL DATA TO SYNTHESIZER
      digitalWrite(7, LOW);                            // Make CS = 0
      shiftOut(13, 12, MSBFIRST, (S_data[n] >> 8));  
      // shift out lowbyte
      shiftOut(13, 12, MSBFIRST, S_data[n]);  
      digitalWrite(7, HIGH);                            // Make CS = 1  
      //****END SENDING DATA****
     n++;
    }
  F_LCD_old=F_LCD;
  }

  while (FreqCounter::f_ready == 0) 
  frq=FreqCounter::f_freq;            // read result of counter (Pin 5 = counter input, Pin 6 reads the Sign (Up/Dwn)
}



