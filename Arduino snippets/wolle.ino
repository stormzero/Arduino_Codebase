/** Hilfsprogramm zur Auswertung der Zähler
// Saved by Simulator for Arduino V0.97
* Maximal 8 SO-Zähler können angeschlossen werden, die mit folgendem Protokoll
* an die serielle Schnittstelle ausgegeben werden:
*
* byte0  byte1     byte2     byte3      ...
* A-H    0-9       0-9       0-9        \n
* Kanal  Millis                         Newline
*
* Die Millis sind dabei die Millisekunden zwischen den letzten beiden Low-High-Flanken
* auf dem angegebenen Kanal.
*/
const byte counterPins[8] = { 2,3,4,5,6,7,8,9 };
unsigned long millisBetween[8];
unsigned long lastMillis[8];
byte lastState[8];

void setup() {
  for (byte i = 0; i < sizeof(counterPins); i++) {
     pinMode(counterPins[i], INPUT);
     digitalWrite(counterPins[i], LOW);
     millisBetween[i] = 0;
     lastMillis[i] = 0;
     lastState[i] = 0;
  }
  Serial.begin(9600);
}

void loop() {
  unsigned char bitMaskToSend = 0;
  unsigned long time = millis();
  for (byte i = 0; i < 8; i++) {
     byte val = digitalRead(counterPins[i]);
     if (val == HIGH && lastState[i] == LOW) {
       millisBetween[i] = time-lastMillis[i];
       lastMillis[i] = time;
       bitSet(bitMaskToSend, i);
     }
     lastState[i] = val;
  }
  for (byte i = 0; i < 8; i++) {
     unsigned long dataToWrite = millisBetween[i];
     if (bitRead(bitMaskToSend,i)) {
       Serial.print((char)('A'+i));
       Serial.println(dataToWrite);
     }
  }
}
