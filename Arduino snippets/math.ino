// Simulate Uno
// Saved by Simulator for Arduino V0.94E


int i,j,k,l,m,n,p;
float f1,f2,f3;

void setup() {
  // put your setup code here, to run once:

 i = min(11,12);
 j = max(45, 560);
 k = abs(-123);
 l = sqrt(25);
 m = sq(3);
 n = pow(2,4);

 f1 = cos(1); 
 f2 = sin(1);
 f3 = tan(1);

 p = 0x1234;
 i = lowByte(p); 
 j = highByte(p); 
 k = bitRead(p,2); 
 bitWrite(p,0,1); 
 bitSet(p,1); 
 bitClear(p,1); 
 m = bit(13); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
