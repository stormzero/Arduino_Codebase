#include <EEPROM.h>
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.96

#define bnTab 4 
uint8_t tabParam[bnTab];
  
void not_working() {
for (uint8_t x=0; x<bnTab; x++) {
 EEPROM.write((x*22),x);
 EEPROM.write(((x*22)+1),0);
 for (int y=2; y<18; y++) {
    EEPROM.write(((x*22)+y),'X');
 }
 EEPROM.write(((x*22)+18),0);  
 uint16_t z=x+300;
 uint8_t a=z>>8;
 uint8_t b=z & 255;
 EEPROM.write(((x*22)+19),a);
 EEPROM.write(((x*22)+20),b);
 EEPROM.write(((x*22)+21),0);  
 }
}

working_fine_but_ugly() {
for (uint8_t x=0; x<bnTab; x++) {
 uint8_t w=0;
 w=(x*22);
 EEPROM.write(w,x);
 w=x*22;
 w=w+1;
 EEPROM.write(w,0);
 for (int y=2; y<18; y++) {
  w=x*22;
  w=w+y;
  EEPROM.write(w,'X');}
 w=x*22;
 w=w+18;
 EEPROM.write(w,0);  
 uint16_t z=x+300;
 uint8_t a=z>>8;
 uint8_t b=z & 255;
 w=x*22;
 w=w+19;
 EEPROM.write(w,a);
 w=x*22;
 w=w+20;
 EEPROM.write(w,b);
 w=x*22;
 w=w+21;
 EEPROM.write(w,0);  
 }
}

void arduino_ok() {
for (uint8_t x=0; x<bnTab; x++) {
 int y=0;
 EEPROM.write((x*22),(uint8_t)x);   //x
 EEPROM.write((x*22+1),0);     //x0
 for (int y=2; y<18; y++) EEPROM.write((x*22+y),'X');
 EEPROM.write((x*22+18),0);  //x0XXXXXXXXXXXXXXXX0
 uint16_t z=x+300;
// uint8_t a=z>>8,b =lowByte(z);
uint8_t a=z>>8;int b =lowByte(z);
 EEPROM.write((x*22+19),a);
 EEPROM.write((x*22+20),b);
 EEPROM.write((x*22+21),0);  //x0XXXXXXXXXXXXXXXX0ab0
 }
}

void setup() {
 not_working();
 arduino_ok();
 working_fine_but_ugly(); 
}
 
void loop() {
} 
