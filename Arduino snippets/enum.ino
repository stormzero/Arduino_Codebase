// Simulate Uno
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95D
// Saved by Simulator for Arduino V0.95B
// Enums are not yet 100% implemented

byte b;
int i;

typedef enum {STATE_1=0, STATE_2, STATE_3} stateType;
enum states {STATE_x, STATE_y, STATE_z} state1;
enum states2 {STATE_11=0, STATE_12, STATE_13} state2a;

stateType state3 = STATE_2;

enum states4 {
 STATE_A=0,
 STATE_B,
 STATE_C
}; 

enum states4 state = STATE_C;

//enum states state1; 
enum states2 state2; 

void setup() {
  // put your setup code here, to run once:
 state1 = STATE_y;
// state1++;
//
 state2 = STATE_13;
// state2+=2;

state3 = STATE_2;

}

void loop() {
  // put your main code here, to run repeatedly:

}
