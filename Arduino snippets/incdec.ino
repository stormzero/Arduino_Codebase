
// Simulate(Uno)
byte i;
int cnt,cnt1,cnt2,cnt3;

void setup() {
  // put your setup code here, to run once:
 DDRD = 0xaa;
 PORTD = 0x55;
 i = PORTD; 
 Serial.begin(9600);
 cnt = 0;
 cnt1 = 0;

}




void loop() {
  // put your main code here, to run repeatedly:

 Serial.print(cnt++);
 Serial.print(",");
 Serial.print(++cnt1);
 Serial.print(",");
 Serial.print(cnt2--);
 Serial.print(",");
 Serial.println(--cnt3);

 if (1) 

    i = 23;

 else 
  
    i= 56; 



 if (i==0) 

    i = 23;

 else if (i>20)
  
    i= 56; 
 else if (i>10)
  
    i= 56; 


}
