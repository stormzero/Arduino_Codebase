// David Pena
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.96.A.3

const int Master = 1;  // 1 = Master Sequencer 
const int Admin = 1;     // 1 = Wind, Water level, Max Height Adjust, Time Clock Audio input Control.
const int Slave  = 0;   // 1 = Slave (Slave and Admin NOT allowed)
const int Unit = 1;    // 1,2,3,4

#include <avr/pgmspace.h>
#include <Wire.h> 
//------------------------- Engine 1 
int Red_1_New = 0;
int Grn_1_New = 0;
int Blu_1_New = 0;
int Wtr_1_New = 0;

int Red_1_Level = 0;
int Red_1_Done = 0;

int Grn_1_Level = 0;
int Grn_1_Done = 0;

int Blu_1_Level = 0;
int Blu_1_Done = 0;

int Wtr_1_Level =0;
int Wtr_1_Done = 0;

unsigned long Tmr_Trans_1 = 0;
unsigned long Temp_1;
unsigned long Trans_Tm_1;
int OffSet_1 = 0;

int Seq_1 = 0;    
int Pri_1 = 0;
int loca_1 = 0;
int Old_loca_1 = 0;
int Seq_Rst_1 = 0;



int Red_1_Def = 0;
unsigned long Red_1_Mills;
unsigned long Red_1_Cnt = 0;
unsigned long Tmr_Red_1 = 0;

int Grn_1_Def = 0;
unsigned long Grn_1_Mills;
unsigned long Grn_1_Cnt = 0;
unsigned long Tmr_Grn_1 = 0;

int Blu_1_Def = 0;
unsigned long Blu_1_Mills;
unsigned long Blu_1_Cnt = 0;
unsigned long Tmr_Blu_1 = 0;

int Wtr_1_Def = 0;
unsigned long Wtr_1_Mills;
unsigned long Wtr_1_Cnt = 0;
unsigned long Tmr_Wtr_1 = 0;



//------------------------- Engine 2 
int Red_2_New = 0;
int Grn_2_New = 0;
int Blu_2_New = 0;
int Wtr_2_New = 0;

int Red_2_Level = 0;
int Red_2_Done = 0;

int Grn_2_Level = 0;
int Grn_2_Done = 0;

int Blu_2_Level = 0;
int Blu_2_Done = 0;

int Wtr_2_Level = 0;
int Wtr_2_Done = 0;


unsigned long Tmr_Trans_2 = 0;
unsigned long Temp_2;
unsigned long Trans_Tm_2;
int OffSet_2 = 0;

int Seq_2 = 0;    
int Pri_2 = 0;
int loca_2 = 0;
int Old_loca_2 = 0;
int Seq_Rst_2 = 0;

int Red_2_Def = 0;
unsigned long Red_2_Mills;
unsigned long Red_2_Cnt = 0;
unsigned long Tmr_Red_2 = 0;

int Grn_2_Def = 0;
unsigned long Grn_2_Mills;
unsigned long Grn_2_Cnt = 0;
unsigned long Tmr_Grn_2 = 0;

int Blu_2_Def = 0;
unsigned long Blu_2_Mills;
unsigned long Blu_2_Cnt = 0;
unsigned long Tmr_Blu_2 = 0;

int Wtr_2_Def = 0;
unsigned long Wtr_2_Mills;
unsigned long Wtr_2_Cnt = 0;
unsigned long Tmr_Wtr_2 = 0;

//--------------------------------------------------- Admin
// Hardware connections

const int Red_Out = 9;      // ~Pin 15,(PWM)LED RED OUT   / MASTER (DO) MSG Strobe
const int Grn_Out = 10;     // ~Pin 16,(PWM)LED GREEN OUT / MASTER (DO) MSG Reset
const int Blu_Out = 11;     // ~Pin 17,(PWM)LED BLUE OUT  / MASTER (D0) Fill Valve
const int Wtr_Out = 3;      // ~Pin 5, (PWM)WATER OUT     / MASTER (DO) Aux Out

const int Wireless_0 = 2;   // Pin 4, MASTER, Wireless b0
const int Wireless_1 = 4;   // Pin 6, MASTER, Wireless b1
const int Wireless_2 = 5;   // ~Pin 11, MASTER Wireless b2
const int Wireless_3 = 6;   // ~Pin 12, MASTER Wireless b3
const int Wireless_4 = 7;   // Pin 13, MASTER Wireless b4
const int Wireless_5 = 8;   // Pin 14, MASTER Wireless b5
const int Wireless_6 = 12;  // Pin 18, MASTER Wireless b6
const int Wireless_7 = 13;  // Pin 19, MASTER Wireless b7

const int Ana_1 = A0;       // Pin 23,(Analog input) MASTER - (Spare analog In)
const int Ana_2 = A1;       // Pin 24,(Analog input) MASTER - (Spare analog In)
const int Ana_3 = A2;       // Pin 25(Analog input) MASTER - (Temperature)  
const int Audio = A3;       // Pin 26(Analog input) MASTER - Audio Frequency 

const int SDA_OUT = A4;         // Pin 27(Analog input, SDA) NASTER 
const int SLC_OUT = A5;         // Pin 28(Analog input, SLC) MASTER

//----------------------------------------------------------------------
int Raw_Max_1 = 0;  // variable to store the value coming from the sensor
int Raw_Max_2 = 0;
int Raw_Max_3 = 0;
int Raw_Max_4 = 0;



unsigned int Stop = 0;
unsigned int Start = 255;

int Old_Ser = 0;
int Ser_Test;
int Ser_See;
int Ser_Funct = 1;
int Ser_Started = 0;

int Learn = 0;
int Here = 1;
int Look = 0;

int Point_A[26];    //  Sequence block offset SET UP IN LEARN CODE

int Big = 0;
int Old_Big = 0;
byte Wireless_Byte = 0;
int Jet_Adjust = 0;

int Step = 0;  

unsigned long WireLess_Mills;
unsigned long WireLess_Time_Cnt;

unsigned long Show_Mills;
unsigned long Show_Time_Cnt;
unsigned long Step_Time;

unsigned long AnaPass_Mills;
unsigned long AnaPass_Time_Cnt;

int Ser[8];
int Var[8];
int Ser_Temp[8];
int Audio_Freq[7];  // Spectrum analyser array
byte Band;

int Audio_Trig_Lev;
int Freq_0;
int Audio_Max;
int Ana_Max_Mills;
int Ana_Max_Cnt;
int Tm_1,Tm_2,Tm_3,Tm_4,Tm_5,Tm_6,Tm_7,Tm_8,Tm_9,Tm_10,Tm_11,Tm_12;

// LCD Parameters
byte lcd_addr = 0x50;                          // default I2C hex address from datasheet for LCD display
byte lcd_clear = 0x51;                         // Command to clear LCD screen
byte lcd_pin = 10;                             // Arduino Pin to drive LCD backlight with PWM
byte lcd_bright = 75;                          // Set Pin driving LED PWM brightness level (0 - 255) (Using 75 for low power)
byte lcd_clear_flag = 0;                       // Variable to clear the screen 1 time after mission count changes to remove old characters
    
byte Dave = 10;

#typedef prog_uint16_t uint16_t;

//------------------------------------------ Master Sequence A -------------
const int Mas_A_Len = 1;
PROGMEM prog_uint16_t Array_Seq_GrprA[]  =  // Array_Seq_GrprA[Step][Unit 0-4]
{  
  0,0,0,0, 50,  //Turn off Engine #2
};

//------------------------------------------ Master Sequence B -------------
const int Mas_B_Len = 1;
PROGMEM prog_uint16_t Array_Seq_GrprB[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  4,4,4,4, 50,  //Turn off Engine #2
};

//------------------------------------------ Master Sequence C -------------
const int Mas_C_Len = 1;
PROGMEM prog_uint16_t Array_Seq_GrprC[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  5,5,5,5, 50,  //Turn off Engine #2
};

//------------------------------------------ Master Sequence D -------------
const int Mas_D_Len = 12;
PROGMEM prog_uint16_t Array_Seq_GrprD[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  6,6,6,6, 100,  //Turn off Engine #2
  5,6,6,5, 10, //    Seq1, Seq 2, Seq 3, Seq 4,  Duration 1/10 Seconds
  6,6,6,6, 100, //
  7,7,7,7, 100,
  7,7,7,8, 5,
  7,7,8,8, 5,
  7,8,8,8, 5,
  8,8,8,8, 100,
  9,8,8,8, 5,
  9,9,8,8, 5,
  9,9,9,9, 100,
  9,9,9,9, 100,
};

//------------------------------------------ Master Sequence E -------------
const int Mas_E_Len = 18;
PROGMEM prog_uint16_t Array_Seq_GrprE[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  11,11,11,11, 50,  //Turn off Engine #2
  12,12,12,12, 50,
  11,12,11,12, 50,
  12,11,12,11, 30,
  12,12,12,12, 30,
  13,12,12,12, 7,
  13,12,13,12, 7,
  13,13,13,12, 7,
  13,13,13,13, 50,
  14,13,13,14, 20,
  13,13,13,13, 10,
  13,14,14,13, 20,
  13,13,13,13, 15,
  5,5,5,5,   30,
  15,5,5,5,  3,
  15,15,5,5,  3,
  15,15,15,5, 3,
  15,15,15,15, 60,
};

//------------------------------------------ Master Sequence F -------------
const int Mas_F_Len = 33;
PROGMEM prog_uint16_t Array_Seq_GrprF[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  16,0,0,0, 3,
  16,16,0,0, 3,
  0,16,16,0, 3,
  0,0,16,16, 3,
  0,0,0,16, 3,
  0,0,0,0, 5,
  16,0,0,0, 1,
  16,16,0,0, 1,
  16,16,16,0, 1,
  0,16,16,16, 1,    //10
  0,16,16,16, 1,
  0,0,16,16, 1,
  0,0,0,16, 1,
  0,0,0,0, 5,
  0,0,0,16, 1,
  0,0,16,16, 1,
  0,16,16,16,  1,
  16,16,16,16, 50,
  5,5,5,5, 4,
  17,5,5,17, 5,//20
  17,17,17,17, 4,
  4,4,4,4, 30,
  18,4,18,4, 6,
  4,18,4,18, 3,
  18,4,18,4, 5,  // 25
  4,18,4,18, 4,
  18,4,18,4, 4,
  4,18,4,18, 4,
  18,18,18,18, 40,
  19,18,18,18, 2,  //30
  19,19,18,18, 2,
  19,19,19,18, 2,
  19,19,19,19, 100,
};

//------------------------------------------ Master Sequence G -------------
const int Mas_G_Len = 34;
PROGMEM prog_uint16_t Array_Seq_GrprG[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  5,5,5,5, 20,  //Turn off Engine #2
  20,20,20,20, 30,
  21,20,20,21, 20,
  20,5,5,5, 10,
  20,5,5,20, 60,
  20,21,21,20, 20, 
  0,0,0,0, 5,
  23,0,0,0, 1,
  23,23,0,0, 1,
  23,23,23, 0, 1,  //10
  23,23,23,23, 40,
  0,23,23,23, 1,
  0,0,23,23,  1,
  0,0,0,23,  1,
  0,0,0,0,  10,

  0,0,0,24,  2,
  0,0,24,24,  2,
  0,24,24,24, 2,
  24,24,24,24, 50,  //20
  23,23,23,23, 5,
  24,24,24,0  ,1,
  24,24,0,0, 1,
  24,0,0,0,  1,
  0,0,0,0, 5,
  25,25,25,25, 30,
  22,25,25,25, 1,
  25,25,25,25, 30,
  25,22,25,25, 1,
  25,25,25,25, 30,  //30
  25,25,22,25, 1,
  25,25,25,25, 30,
  25,25,25,22,1,
  25,25,25,25, 20,
};

//------------------------------------------ Master Sequence H -------------
const int Mas_H_Len = 3;
PROGMEM prog_uint16_t Array_Seq_GrprH[]  =  // Array_Seq_GrprB[Step][Unit 0-4]
{  
  0,0,0,0, 2,  //Turn off Engine #2
  14,14,14,14, 50, //    Seq1, Seq 2, Seq 3, Seq 4,  Duration 1/10 Seconds
  15,15,15,15, 100, //
};

//---------------------------------------------- Output Sequence Map A

const int Seq_Len_A = 137;
PROGMEM prog_uint16_t Array_Seqs_A[] =  // { Red, Green,  Blue,  Water,  Transition 1/10 Seconds}
{
  // 0    
  0  ,0  ,0  ,0    ,1003,            // #0  Immidiate off
  0  ,0  ,0  ,0    ,1050,          // #1     Slow Off
  100 ,100  ,100  ,0    ,1010,       // #2   Just Lights full
  0  ,0  ,0  ,100    ,1010,            // #3   Just Water full
  50  ,50  ,50  ,100    ,1010,            // #4   White 50%, Water full
  100  ,100  ,100  ,100    ,1010,            // #5   White & Water full
  //6------------------------------------------------------------------------

  50  ,50  ,50  ,30    ,90,            // #6   White & Water Bars 5 sec
  50  ,50  ,50  ,80    ,90, 
  50  ,50  ,50  ,50    ,90, 
  50  ,50  ,50  ,100    ,1090, 
  //10

    50  ,50  ,50  ,70    ,100,            // #7   White & Water bars 1 sec
  50  ,50  ,50  ,80    ,100, 
  50  ,50  ,50  ,40    ,100, 
  50  ,50  ,50  ,100    ,1050,
  //14

  50  ,100  ,50  ,100    ,70,         // #8   Shades of RGB & Water Bars 1 sec
  50  ,50  ,50  ,70      ,50, 
  50  ,50  ,100  ,100    ,70, 
  50  ,50  ,50  ,70      ,50, 
  100  ,50  ,50  ,100    ,80, 
  50  ,50  ,50  ,70      ,1050, 
  // 20

    50  ,100  ,50  ,100    ,50,         // #9   Shades of color & Water Triangle 1 sec
  50  ,100  ,100  ,70    ,60,           //     Some time variations
  100  ,50  ,100  ,80    ,100, 
  50  ,30  ,50  ,70    ,40, 
  100  ,50  ,100  ,100    ,10, 
  50  ,50  ,50  ,70    ,1030, 
  // 26 --------------------------------------------------------------------

  0  ,100  ,0  ,100    ,10,         // #10   Full color & Water Triangle 1 sec
  0  ,100  ,100  ,70    ,50,           //     Some time variations
  100  ,0  ,100  ,80    ,10, 
  0  ,100  ,0  ,70    ,20, 
  100  ,100  ,0  ,80    ,10, 
  0  ,0  ,100  ,90    ,10, 
  0  ,100  ,100  ,90    ,10, 
  0  ,0  ,100  ,90    ,10, 
  0  ,100  ,0  ,90    ,1010,
  // 35

  40  ,0  ,0   ,0  ,10,            // #11  Spike Wave Triangle
  100  ,0  ,0   ,100  ,40,          // Red tip, blue tail
  45  ,0  ,100  ,50    ,1030,
  // 38

  0  ,40  ,0   ,0  ,10,            // #12  Spike Wave Triangle
  0  ,100  ,0   ,100  ,40,          // Green tip, amber tail
  45  ,50  ,0  ,50    ,1040,
  // 41

  0  ,0  ,0   ,40  ,10,            // #13  gental Wave Triangle
  100  ,100  ,100   ,100  ,20,          // white tip, gray tail
  45  ,45  ,45  ,0    ,10,
  45  ,45  ,45  ,0    ,1030,
  // 45

  0  ,0  ,50  ,0  ,4,            // #14  Dual Wave Triangle
  0  ,0  ,80   ,100  ,6,          // Blue tip, Violet tail
  0  ,0  ,100  ,50    ,5,
  0  ,0  ,20    ,90  ,3,
  20  ,0  ,20  ,0  ,1010,
  // 50

    0  ,100  ,100  ,100  ,2,            // #15 Triple Wave Triangle
  0  ,100  ,100  ,50    ,5,
  0  ,100  ,0  ,90    ,2,
  0  ,100  ,0  ,40    ,5,
  0  ,0  ,100  ,80    ,2,
  0  ,0  ,100  ,20    ,5,
  0  ,0  ,0    ,0    ,1030,
  //57 ----------------------------------------------------------------------

  0  ,0  ,0  ,0  ,3,                // #16 Bar steps up
  20  ,0  ,0  ,20  ,5,                //  Red to Amber
  40  ,10  ,0  ,40  ,5,
  60  ,25  ,0  ,60  ,5,
  80  ,50  ,0  ,80  ,5,
  100  ,100  ,0  ,100  ,5,
  0  ,0  ,0  ,0  ,1020,
  // 64

  100  ,100  ,0  ,100  ,3,          // #17 Bars Step down
  50  ,80  ,0  ,80  ,5,              // Amber to green
  25  ,60  ,0  ,60  ,5,
  10  ,40  ,0  ,40  ,5,
  0  ,20  ,0  ,20  ,5, 
  0  ,0  ,0  ,0  ,1020,
  // 70

    0  ,0  ,0  ,0  ,5,            // #18 Triple bars
  0  ,50  ,0  ,50  ,10,            // Bars Grn, Wht, Amber
  0  ,0  ,0  ,0  ,10,
  100  ,100  ,100  ,100  ,5,
  0  ,0  ,0  ,0  ,15,
  75  ,0  ,75  ,75  ,20,
  0  ,0  ,0  ,0  ,1025,
  // 77

  0  ,0  ,0  ,0  ,5,          // #19 Step un and down bars
  40  ,20  ,40  ,40  ,15,      // Violet on top
  0  ,0  ,0  ,0  ,15,
  60  ,0  ,60  ,60  ,15,
  0  ,0  ,0  ,0  ,15,
  100  ,0  ,100  ,100  ,15,
  0  ,0  ,0  ,0  ,15,
  60  ,40  ,60  ,60  ,15,
  0  ,0  ,0  ,0  ,20,
  40  ,20  ,40  ,40  ,15,
  0  ,0  ,0  ,0  ,1025,
  // 88

  0  ,0  ,0  ,0  ,15,          // #20 Step up, pop and down bars
  0  ,0  ,0  ,40  ,7,          // 
  100  ,0  ,0  ,0  ,3,
  0  ,0  ,0  ,40  ,4,
  0  ,0  ,0  ,80  ,7,          
  100  ,0  ,0  ,0  ,3,
  0  ,0  ,0  ,80  ,4,
  0  ,0  ,0  ,100  ,7,          
  100  ,0  ,0  ,0  ,3,
  0  ,0  ,0  ,100  ,4,
  0  ,0  ,0  ,80  ,7,          
  0  ,0  ,0  ,40  ,4,
  0  ,0  ,0  ,80  ,7,          
  0  ,0  ,0  ,0  ,1040,
  // 102  

  100  ,0  ,0  ,0    ,1,     // Seq 21  
  100  ,100  ,0  ,70    ,2,
  100  ,0  , 100  , 70  ,3,
  0    ,100  ,0  ,4  ,4,
  0  ,100  ,100  ,60  ,5,
  100  ,100  ,100  ,60  ,6,
  100  ,0  ,100  ,10  ,1010,
  // 109

  10  ,0  ,0  ,80  ,2,    // Seq 22
  10  ,100  ,0  ,80  ,2,
  100  ,100  ,100  ,2  ,2,
  0  ,0  ,0  ,2  ,2,
  50  ,100  ,100  ,80  ,2,
  0  ,100  ,100  ,80  ,2,
  100  ,0  ,100  ,80  ,1002,
  // 116

  100  ,0  ,0  ,50  ,5,    // Seq 23
  100  ,100  ,0  ,100  ,0,
  100  ,0  ,100  ,100  ,10,
  0  ,100  ,0  ,0  ,0,
  0  ,100  ,100  ,50  ,5,
  0  ,100   ,100  ,75  ,0,
  100  ,0  ,100  ,100  ,1010,
  // 123

  100  ,0  ,0  ,40  ,4, // Seq 24
  100  ,50  ,0  ,45  ,0,
  50  ,0  ,100  ,50  ,4, 
  0  ,100  ,0  ,60  ,0,
  0  ,0  ,100  ,70  ,4,
  0  ,100  ,50  ,80  ,0,
  50  ,0  ,100  ,90 ,1005,
  // 130

  100  ,0  ,0  ,95  ,1,  // Seq 25
  100  ,50  ,0  ,90  ,1, 
  50  ,0  ,100  ,90  ,1,
  0  ,100  ,0  ,95  ,1,
  0  ,0  ,100  ,90  ,1,
  0  ,100  ,50  ,95  ,1, 
  50  ,0  ,100  ,90  ,1001,

  // 137
};

//-----------------------------------------------------------
void setup() 
{  
  Serial.begin(9600);
  pinMode(2, INPUT);    //  Serial Input 

  // initialize the Wireless inputs:
  pinMode(Wireless_0, INPUT); 
  pinMode(Wireless_1, INPUT); 
  pinMode(Wireless_2, INPUT); 
  pinMode(Wireless_3, INPUT); 
  pinMode(Wireless_4, INPUT); 
  pinMode(Wireless_5, INPUT); 
  pinMode(Wireless_6, INPUT); 
  pinMode(Wireless_7, INPUT); 


  pinMode(Red_Out, OUTPUT);
  pinMode(Grn_Out, OUTPUT);
  pinMode(Blu_Out, OUTPUT);
  pinMode(Wtr_Out, OUTPUT);


  int prescalerMask = 0x07; //create a variable called prescalerVal and set it equal 
  //to the binary number "00000111"
  TCCR1B &= ~prescalerMask; //AND the value in TCCR0B with binary number "11111000"
  TCCR2B &= ~prescalerMask; //AND the value in TCCR0B with binary number "11111000" 

  int prescalerVal = 2; //set prescalerVal equal to binary number "00000010" 

  TCCR1B |= prescalerVal; //OR the value in TCCR0B with binary number "00000010"
  TCCR2B |= prescalerVal; //OR the value in TCCR0B with binary number "00000010"

//LCD Parameter settings
 delay(500);                       // Allow LCD microcontroller to wake up.          
 Wire.begin();                     // Initialize Wire library

// Wire library expects 7-bit value for address and shifts left appending 0 or 1 for read/write
  // Adjust address to match what Wire is expecting (shift it right one bit)
      lcd_addr = lcd_addr >> 1;

      ChangeContrastLCD(0x23);          // Set Contrast 0x1E is 30, 0x23 is 35. Valid values of 1 - 50      
 
      //Send lcd clear command & splash screen    
      PrintLCD(lcd_clear, 0, "Wise Fountains"); // PrintLCD(command, cursor position, ascii text); 0 = no command; cursor position 0 = row 1, 64 = row 2      
      PrintLCD(0, 64, " David Pena");       

      delay(3000); // Delay for Splash Screen



} //  End Setup



void loop() 

{ //    ---------- start of main loop

    Learn_();    // Do once to find all sequence starting address


  if (Master == 1)  // ----------------------------------------- Master ----------
  {
    Wireless1();
    Spectrum1();
    Master1();
    
  }  


  if (Slave == 1)   //  --------------------------------------  Slave -------------
   {
    Slave1();
   }
   


}   // go back to:    Main Loop


// ----------------------------------------------------------------------------------------------------------------------
//
// PrintLCD (command, cursor position, ASCII text): 0 = no command; cursor position 0 = row 1, 64 = row 2
// Send ASCII to Newhaven Serial LCD in I2C mode
//
// ----------------------------------------------------------------------------------------------------------------------
void PrintLCD(byte cmd, byte pos, char* text)
{
      // Perform command if sent (i.e. 0x51 clear screen). 0 = no command required
      if(cmd >0)
        {

        Wire.beginTransmission(lcd_addr);
        Wire.write(0xFE); //LCD Command
        Wire.write(cmd);
        Wire.endTransmission(); 

        }
      
      // Position cursor and send text to LCD
      Wire.beginTransmission(lcd_addr);
      Wire.write(0xFE); //LCD Command
      Wire.write(0x45); //Set Cursor pos
      Wire.write(pos);  //Set Cursor pos
      Wire.write(text); //LCD
      Wire.endTransmission();  
}


// ----------------------------------------------------------------------------------------------------------------------
//
// ChangeContrastLCD(contrast value)
//
// Change default contrast 0xFE 0x52 (Contrast in Hex) 1-50, 40 is default
// Note: Brightness changes is no longer using this routine with the new display
// Contrast 0x1E is 30, 0x23 is 35. Valid values of 1 - 50
// ----------------------------------------------------------------------------------------------------------------------
void ChangeContrastLCD(byte value)
{
        Wire.beginTransmission(lcd_addr);      
        Wire.write(0xFE);        // LCD Command
        Wire.write(0x52);        // Contrast 0x52
        Wire.write(value);       // Contrast Value
        Wire.endTransmission();
}


// ----------------------------------------------------------------------------------------------------------------------
//
// One Wire iButton DataLogger Programmer Main Loop
//
// ----------------------------------------------------------------------------------------------------------------------

/*
void loop(void) {
  
for (int Move = 0; Move < 16; Move++)
    {  
    PrintLCD(lcd_clear, Move, "David Pena");
  
     delay(400); // TODO: Keep this delay in unless search polling is implemente
    }
  
}
*/



