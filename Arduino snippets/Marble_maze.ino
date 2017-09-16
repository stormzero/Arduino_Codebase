// Controlling a servo position using a potentiometer (variable resistor) 
// Saved by Simulator for Arduino V0.96.0.2
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo table_1_servo_1;  // create servo object to control a servo 
Servo table_1_servo_2;  // create servo object to control a servo 
Servo table_2_servo_1;  // create servo object to control a servo 
Servo table_2_servo_2;  // create servo object to control a servo 

 
int table_1_pot_1 = 0;  // analog pin used to connect the potentiometer 1 table 1
int table_1_pot_2 = 1;  // analog pin used to connect the potentiometer 2 table 1
int table_2_pot_1 = 2;  // analog pin used to connect the potentiometer 1 table 2
int table_2_pot_2 = 3;  // analog pin used to connect the potentiometer 2 table 2

int val_pot_1 ;    // variable to read the value from the analog pin 
int val_pot_2 ;    
int val_pot_3 ;    
int val_pot_4 ;    
 
void setup() 
{ 
  table_1_servo_1.attach(5);  // attaches the servo on pin 5 to the servo object 
  table_1_servo_2.attach(6);  
  table_2_servo_1.attach(9);  
  table_2_servo_2.attach(10);  
} 
 
void loop() 
{ 
  val_pot_1 = analogRead(table_1_pot_1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val_pot_1 = map(val_pot_1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  table_1_servo_1.write(val_pot_1);                  // sets the servo position according to the scaled value 
 
  val_pot_2 = analogRead(table_1_pot_2);            // reads the value of the potentiometer (value between 0 and 1023) 
  val_pot_2 = map(val_pot_2, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  table_1_servo_2.write(val_pot_2);                  // sets the servo position according to the scaled value 
 
  val_pot_3 = analogRead(table_2_pot_1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val_pot_3 = map(val_pot_3, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  table_2_servo_1.write(val_pot_3);                  // sets the servo position according to the scaled value 
 
  val_pot_4 = analogRead(table_2_pot_2);            // reads the value of the potentiometer (value between 0 and 1023) 
  val_pot_4 = map(val_pot_4, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  table_2_servo_2.write(val_pot_4);                  // sets the servo position according to the scaled value 
    
  delay(15);                           // waits for the servo to get there 
}
