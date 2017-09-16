
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
//***************************************

//Define LED pins

int zero_in = 0; //set pin 0 as input switch

int zero_detected = 20; //set pin 20 as output LED

byte do_something = 0 //my variable to keep up with things needing
//to be done
//bit 0 = 'zero in' was detected

void setup()
{ 

// Define outputs.
//pinMode(zero_detected, OUTPUT);
pinMode(A5, OUTPUT);
pinMode(A5, INPUT_PULLUP);

//Define inputs
pinMode(zero_in, INPUT)
}

// this loop routine repeats forever:
void loop() {

//*********
if (digitalRead(zero_in) == HIGH) 
{
digitalWrite(zero_detected, HIGH);
bitWrite(do_something,3,1);
}
else
{
digitalWrite(zero_detected, LOW);
bitWrite(do_something,3,0);
}
}
