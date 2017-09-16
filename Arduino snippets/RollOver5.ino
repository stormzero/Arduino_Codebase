unsigned long MX; 

void setup() {                
  Serial.begin(9600);
  
  Serial.println("MAX Test1");
  MX = 0xFFFFFFFF; //4294967295;
  Serial.print("MX="+String(MX));
  Serial.print(";Hex="+String(MX,HEX));
  Serial.println(";Bin="+String(MX,BIN));
  
 // Serial.println("MAX+1 Test");
 // MX = MX+1;
 // Serial.print("MX+1="+String(MX));
 // Serial.print(";Hex="+String(MX,HEX));
 // Serial.println(";Bin="+String(MX,BIN));
  
  Serial.println("MAX Test2");
  MX = 0x7FFFFFFF;
  Serial.print("MX="+String(MX));
  Serial.print(";Hex="+String(MX,HEX));
  Serial.println(";Bin="+String(MX,BIN));
  
  Serial.println("MAX+1 Test");
  MX = MX+1;
  Serial.print("MX+1="+String(MX));
  Serial.print(";Hex="+String(MX,HEX));
  Serial.println(";Bin="+String(MX,BIN));
  
  
}

void loop() { 
  while(1);
}




