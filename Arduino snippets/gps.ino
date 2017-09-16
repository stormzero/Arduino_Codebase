
// Saved by Simulator for Arduino V0.98.B.2
// SerialIn(Sats HDOP Latitude Longitude Fix  Date       Time       Date Alt     Course Speed Card  Distance Course Card  Chars Sentences Checksum           (deg)    (deg)                        Age                     Age         (m)     --- from GPS ----  ---- to London  ----  RX    RX        Fail --------------------------------------------------------------------------------------------------------------------------------------    6    280    38.64370 -121.07538 117  02/18/2013 17:05:07   137  169.70  7.79   0.00  N     8473     33.35  NNE   358   3         2 )

string s;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
}

void loop() {
  // read the sensor:
	s = '';
  while (Serial.available()) {
	s = s + Serial.read();  
}
	Serial.print(s);

}




