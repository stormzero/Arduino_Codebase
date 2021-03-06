{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\f0\fs-24 /*\par
  Gadget Factory\par
  Papilio One QuickStart Example\par
 \par
 Pressing any of the 4 pushbuttons on the Button/LED Wing will light the corresponding LED. \par
 \par
 BPW5007 Button/LED Wing Reference:\par
 http://www.gadgetfactory.net/gf/project/bpw5007-butnled/\par
 \par
 Hardware:\par
 * Connect a Button/LED Wing to any available Wing Slot\par
\par
 created 2010\par
 by Jack Gassett from existing Arduino code snippets\par
 http://www.gadgetfactory.net\par
 \par
 This example code is in the public domain.\par
 */\par
\par
int ledPins[] = \{ \par
  0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46  \};       // an array of pin numbers to which LEDs are attached\par
int ledCount = 24;           // the number of pins (i.e. the length of the array)\par
\par
int buttonPins[] = \{ \par
  1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47 \};       // an array of pin numbers to which Buttons are attached\par
int buttonCount = 24;           // the number of pins (i.e. the length of the array)\par
\par
\par
\par
// variables will change:\par
int buttonState = 0;         // variable for reading the pushbutton status\par
int thisPin;\par
int ledState = LOW;\par
\par
// first visible ASCIIcharacter '!' is number 33:\par
int thisByte = 33; \par
// you can also write ASCII characters in single quotes.\par
// for example. '!' is the same as 33, so you could also use this:\par
//int thisByte = '!'; \par
\par
// Simulate(Papilio)\par
\par
void setup() \{\par
  // initialize the LED pins as an output:\par
  for (int thisPin = 0; thisPin < ledCount; thisPin++)  \{\par
    pinMode(ledPins[thisPin], OUTPUT);  \par
  \}\par
  \par
  // initialize the pushbutton pin as an input:\par
  for (int thisPin = 0; thisPin < ledCount; thisPin++)  \{\par
    pinMode(buttonPins[thisPin], INPUT);      \par
  \}  \par
  \par
  //Setup Serial port and send out Title\par
  Serial.begin(9600); \par
\par
  // prints title with ending line break \par
  Serial.println("ASCII Table ~ Character Map"); \par
\}\par
\par
void loop()\{\par
  //This sends the ASCII table to the serial port.\par
  \par
  // prints value unaltered, i.e. the raw binary version of the \par
  // byte. The serial monitor interprets all bytes as \par
  // ASCII, so 33, the first number,  will show up as '!' \par
  Serial.print(thisByte, BYTE);    \par
\par
  Serial.print(", dec: "); \par
  // prints value as string as an ASCII-encoded decimal (base 10).\par
  // Decimal is the  default format for Serial.print() and Serial.println(),\par
  // so no modifier is needed:\par
  Serial.print(thisByte);      \par
  // But you can declare the modifier for decimal if you want to.\par
  //this also works if you uncomment it:\par
\par
  // Serial.print(thisByte, DEC);  \par
\par
\par
  Serial.print(", hex: "); \par
  // prints value as string in hexadecimal (base 16):\par
  Serial.print(thisByte, HEX);     \par
\par
  Serial.print(", oct: "); \par
  // prints value as string in octal (base 8);\par
  Serial.print(thisByte, OCT);     \par
\par
  Serial.print(", bin: "); \par
  // prints value as string in binary (base 2) \par
  // also prints ending line break:\par
  Serial.println(thisByte, BIN);   \par
\par
  // if printed last visible character '~' or 126, stop: \par
  if(thisByte == 126) \{     // you could also use if (thisByte == '~') \{\par
    thisByte = 33;\par
  \} \par
  // go on to the next character\par
  thisByte++;  \par
  \par
  //This section blinks the LED's and keeps them solid if a button is pressed. \par
  delay(200);                  // wait for a second \par
  ledState = !ledState;  \par
  for (int thisPin = 0; thisPin < buttonCount; thisPin++)  \{\par
    // read the state of the pushbutton value:\par
    buttonState = digitalRead(buttonPins[thisPin]);\par
  \par
    // check if the pushbutton is pressed.\par
    // if it is, the buttonState is HIGH:\par
    if (buttonState == HIGH) \{     \par
      // turn LED on:    \par
      digitalWrite(ledPins[thisPin], HIGH);  \par
    \} \par
    else \{\par
      // toggle LED:\par
      digitalWrite(ledPins[thisPin], ledState); \par
    \}\par
  \}\par
\}\par
\par
}
 