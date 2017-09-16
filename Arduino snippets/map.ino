//I would expect having the rightmost bytes {1,68} would 
// Saved by Simulator for Arduino V0.98.A.6
//map to an integer value of 324 (e.g. 256 + 68) for both 
//int and long. The long starts at byteArray[0] and the int starts at byteArray[2]
byte byteArray[] = {0,0,1,68};
static char stringBuffer[50];

void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(1000);
  long *longPointer = (long*)byteArray;
  int *intPointer = (int*)(byteArray+2);
  sprintf (stringBuffer, "Long, Int, Bytes: %ld, %i, %i %i %i %i --- ;) \r\n", *longPointer, *intPointer, byteArray[0], byteArray[1], byteArray[2], byteArray[3]);
  Serial.print(stringBuffer);
  Serial.println();
}
