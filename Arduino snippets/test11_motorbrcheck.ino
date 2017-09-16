int motor1 = 5;   // output for motor1 on 5pin(pwm)
// Saved by Simulator for Arduino V0.95A
int motor2 = 6;   // output for motor2 on 6pin(pwm)
int analogpin0 = 0;  // select the pin for analog0 input
int a_input = 0;  // input data from ADC

int i;


void setup() {
  pinMode(motor1, OUTPUT);  // declare the motor1 as an OUTPUT
  pinMode(motor2, OUTPUT);  // declare the motor1 as an OUTPUT
  
  /*** make motor stop  ***/
  analogWrite(motor1, 0);
  analogWrite(motor2, 0);
  
  Serial.begin(9600);

  Serial.println("start");

}

void loop() {

  a_input = analogRead(analogpin0);  //read data from analog0 pin

  if (a_input > 512) {

    /*** cw ***/
    analogWrite(motor1, (a_input - 512)/2 );
    analogWrite(motor2, 0);
    Serial.print("plus");
    Serial.println((a_input - 512)/2);
    
  } else if (a_input < 512) {
    /*** ccw ***/
    analogWrite(motor1, 0);
    analogWrite(motor2, 255 - (a_input /2) );
    Serial.print("minus");
    Serial.println(255 - (a_input /2));
   
  } else {
    /*** stop ***/
    analogWrite(motor1, 0);
    analogWrite(motor2, 0);
    Serial.println("center");
  }

  delay(10);

}
