
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.96.A.3
// Demo 250ms pin toggle using interrupt
int pin = 13;

int PinMasseLeds [8] = {38, 40, 41, 42, 43, 44, 45, 46}; //pin 18, 20, 21, 22, 23, 24, 25, 26
int PinPlusLeds [8] = {22, 24, 26, 28, 30, 32, 34, 36}; //pin 2, 4, 6, 8, 10, 12, 14, 16
int PinMasseBp [7] = {39, 41, 42, 43, 44, 45, 46}; // pin 19, 21, 22, 23, 24, 25, 26
int PinPlusBp [11] = {26, 28, 29, 30, 31, 32, 33, 35, 37, 38, 40}; // pin 6, 8, 9, 10 ,11, 12, 13, 15, 17, 18, 20
int pinmasse;//multiplexage pin led
int pinplus;//multiplexage pin led
int ligne;
int colonne;

boolean LEDS [8][8]; //matrice LEDS [ligne][colone]


void setup()
{
  pinMode(2, OUTPUT);
  pinMode(13, INPUT);
  attachInterrupt(0, blink, CHANGE); // setup interrupt call blink() on pin0 change
}

void loop()
{
 digitalWrite(2,HIGH);
 delay(125);
 digitalWrite(2,LOW);
 delay(125);
}

void blink()
{
  digitalWrite(13,!digitalRead(13));
}


