long MXSL;
unsigned long MXUL;
unsigned long WaitUntil = 0x00000fff;

void setup() {                
  Serial.begin(9600);
  
  Serial.println("MAX Test for signed long");
  MXSL = 0x7FFFFFFF;  //Max for signed long 
  Serial.print("MXSL="+String(MXSL,DEC));
  Serial.print(";Hex="+String(MXSL,HEX));
  Serial.println(";Bin="+String(MXSL,BIN));
  
  Serial.println("MAX+1 Test");
  MXSL = MXSL+1;
  Serial.print("MXSL+1="+String(MXSL));
  Serial.print(";Hex="+String(MXSL,HEX));
  Serial.println(";Bin="+String(MXSL,BIN));
  
  Serial.println("MAX Test for unsigned long");
  MXUL = 0xFFFFFFFF; //Max for undigned value
  Serial.print("MXUL="+String(MXUL,DEC));
  Serial.print(";Hex="+String(MXUL,HEX));
  Serial.println(";Bin="+String(MXUL,BIN));
  
  Serial.println("MAX+1 Test");
  MXUL = MXUL+1;
  Serial.print("MXUL+1="+String(MXUL));
  Serial.print(";Hex="+String(MXUL,HEX));
  Serial.println(";Bin="+String(MXUL,BIN));
  
  //Problem 2:Fail to execute the instruction below
  int Val = (unsigned long)(WaitUntil-millis() )/1000;
  Serial.println("Val="+String(Val,DEC));
}

void loop() { 
  while(1);
}




