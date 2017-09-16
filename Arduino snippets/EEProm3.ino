#include <EEPROM.h>

long VIn;
//unsigned long VIn;
long VOut;

void setup()
{
  Serial.begin(9600);
  VIn = 200000;
//  VIn = 4294967295;
  Serial.print("VIn=");
  PrintDecBin(VIn);
  WriteLog(VIn);
  VOut = ReadLog(VOut);
  Serial.print("VOut=");PrintDecBin(VOut);
}  
  
void loop()
{
  while(1);
}

void WriteLog(long ValueIn) 
{
  int Address = 0;
  byte BT4, BT3, BT2, BT1;
  
  /*-----------------------EXPLANATION-------------------------
  Break ValueIn=Eq 200000 (32 bytes) into 4 values each 8 bytes:
    InValue =00000000 00000011 00001101 01000000 (Dec=200000)
    BT4     = 00000000 (Dec=0)
    BT3     = 00000011 (Dec=3)
    BT2     = 00001101 (Dec=13)
    BT1     = 01000000 (Dec=64)
  
  //SIMULATOR FAILS TO EXEC THE BREAKUP CORRECTLY
  ---------------------------------------------------------------*/
  BT1 = ValueIn & 0xff;       //BT1 = 199488 (with wrong Error Message)
  BT2 = (ValueIn >> 8) & 0xff;  //BT2 = 269 
  BT3 = (ValueIn >> 16)&0xff; //BT3 = 28059
  BT4 = (ValueIn >> 24)&0xff; //BT4 = 6895
  Serial.println("The four bytes written are:");
  Serial.print("BT1=");PrintDecBin(BT1);
  Serial.print("BT2=");PrintDecBin(BT2);
  Serial.print("BT3=");PrintDecBin(BT3);
  Serial.print("BT4=");PrintDecBin(BT4);
  
  EEPROM.write(Address,   BT1);
  EEPROM.write(Address+1, BT2);
  EEPROM.write(Address+2, BT3);
  EEPROM.write(Address+3, BT4);
}//WriteTripLog

long ReadLog(long ValueOut) 
{

  int Address = 0;
  //Read the Value that was broken into 4 bytes
  byte BT1, BT2, BT3, BT4;
  
  Address = 0;
  BT1      = EEPROM.read(Address);
  BT2      = EEPROM.read(Address+1);
  BT3      = EEPROM.read(Address+2);
  BT4      = EEPROM.read(Address+3);
  //Put the 4 bytes together for long int
  int i;  
  for (i=0; i<8; i++) bitWrite(ValueOut,i,   bitRead(BT1,i)); 
  for (i=0; i<8; i++) bitWrite(ValueOut,i+8, bitRead(BT2,i)); 
  for (i=0; i<8; i++) bitWrite(ValueOut,i+16,bitRead(BT3,i)); 
  for (i=0; i<8; i++) bitWrite(ValueOut,i+24,bitRead(BT4,i)); 
    return(ValueOut);
}//ReadTripLog

void PrintDecBin(long Value) {
  /*---SHORTENED VERSION GIVES ERROR IN SIMULATOR--
     Serial.println(String(Value,DEC)+"/Bin="+
                 String(Value,BIN)); 
    ----------------------------------------------*/
  String Info;
  Info = String(Value,DEC);
  Info = Info + "/Bin=";
  Info = Info + String(Value,BIN);
  Serial.println(Info);
}




