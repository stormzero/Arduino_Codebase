char singleChar;

String multiChar = "Hello World";

int myOUTPUT = OUTPUT;  // error: unable to find OUTPUT which is an Arduino
//constant

void setup()
{
  singleChar = multiChar[1];    // unable to find multiChar[1] which is adeclared array

  pinMode(1,myOUTPUT);  // if the simulator ever got this far it would saythat myOUTPUT couldn't be found
                                // again, the Arduino IDE has no problemwith this code.

}

void loop() { }
