
// Saved by Simulator for Arduino V0.98B



const int sensor1Pin   = 0;
const int sensor2Pin   = 1;
const int alertPin      = 2;
const int mprime       = 16667;
const int bprime       = 15;
const int k            = 10;
const int maxdistance1  = 200;
const int alertdistance1 = 80;
const int alertdistance2 = 80;
int sensor1Value = 0;
int distance1 = 0;
int sensor2Value = 0;
int distance2 = 0;
void setup() {

  pinMode(alertPin, OUTPUT);
pinMode(13, OUTPUT);





}
void loop() {
  

  

sensor1Value = readSensor1();
sensor2Value = readSensor2();
distance1 = (mprime / (sensor1Value + bprime)) - k;
distance2 = (mprime / (sensor2Value + bprime)) - k;
soundAlert(distance1);
}
int readSensor1() {
int _i;
int _sensor1Value = 0;
for(_i = 0; _i < 5; _i ++) {
_sensor1Value += analogRead(sensor1Pin);
delay(10);
}
_sensor1Value = _sensor1Value / 5;
return _sensor1Value;
}
int readSensor2() {
int _i;
int _sensor2Value = 0;
for(_i = 0; _i < 5; _i ++) {
_sensor2Value += analogRead(sensor2Pin);
delay(10);
}
_sensor2Value = _sensor2Value / 5;
return _sensor2Value;
}
void soundAlert(int _distance1) {
if (_distance1 < alertdistance1 && distance2 > alertdistance1)
digitalWrite(alertPin, HIGH);
digitalWrite(13, HIGH);

}
