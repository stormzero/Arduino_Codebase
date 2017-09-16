float fltNumber;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
fltNumber = 1.25;
  Serial.println(fltNumber); 
 
fltNumber = 5/2;
  Serial.println(fltNumber); 
 
 
fltNumber = float(5/2);
  Serial.println(fltNumber); 
 
fltNumber = 5/float(2);
  Serial.println(fltNumber); 

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
