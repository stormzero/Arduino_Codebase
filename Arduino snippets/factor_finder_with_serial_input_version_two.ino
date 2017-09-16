unsigned long number = 0;
// Saved by Simulator for Arduino V0.97.B.2
unsigned long divider;

// SerialIn(72)

void setup(){
  Serial.begin(9600);
  Serial.println("Please enter the number that you want to factor (Less than  4,294,967,295 and no commas).");
  number = getULongFromSerialMonitor();
  Serial.print(number);
  Serial.println(" is divisible by: ");
}

void loop(){
  divider += 1;
  if(number%divider == 0 && number > 0){
    Serial.println(divider);
    delayMicroseconds(100);
  }
  if(number == 0){
    Serial.println("Everything except for zero.");
    Serial.println("Please enter the number that you want to factor (Less than  4,294,967,295 and no commas).");
    number = getULongFromSerialMonitor();
    Serial.print(number);
    Serial.println(" is divisible by: ");
    divider = 0;
  }
  if(number == divider){
    Serial.println("Please enter the number that you want to factor (Less than  4,294,967,295 and no commas).");
    number = getULongFromSerialMonitor();
    Serial.print(number);
    Serial.println(" is divisible by: ");
    divider = 0;
  }
}

unsigned long getULongFromSerialMonitor(){
  char inData[20];  
  unsigned long ulong = 0;    
  int x=0;  
  while (x<1){  
    String str;   
    if (Serial.available()) {
      delay(100);
      int i=0;
      while (Serial.available() > 0) {
        char  inByte = Serial.read();
        str=str+inByte;
        inData[i]=inByte;
        i+=1;
        x=2;
        }
      ulong = atof(inData);
      memset(inData, 0, sizeof(inData));  
    }
  }
  return ulong; 
}

