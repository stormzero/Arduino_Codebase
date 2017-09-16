/*
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.1

 * Hello World
 * Ausgabe auf der Seriellen Schnittstelle
 * Das "Serial Monitor"-Fenster muss zur Beobachtung geoeffnet sein.
 */
void setup(){ 
  // Initialisierung der seriellen Schnittstelle
  Serial.begin(9600); // Standardeinstellung 9600 aber auch 19200 Baud moeglich

  // Sendet eine Zeichenkette + Zeilenwechsel zur seriellen Schnittstelle
  Serial.print("Hello World"); 
//  Serial.print("Line2"); 

  Serial.print("\rsame line?"); 
pinMode(3,OUTPUT);

  // Kommentieren Sie die folgenden Ausgabeanweisungen
  Serial.println(123);
  Serial.println(1.23456);
  Serial.println('1');
  Serial.println(123, BIN);
  Serial.println(123, OCT);
  Serial.println(123, DEC); 
  Serial.println(123, HEX);
  Serial.println(1.23456, 0);
  Serial.println(1.23456, 2);
  Serial.println(1.23456, 4);
  
  Serial.print("Jetzt einmal write:");
  Serial.write(123);
  Serial.println();
  
  Serial.print("*** ");
  Serial.print("Sonderzeichen");
  Serial.println(" ***");
  
  Serial.println("n -> \n <-");
  Serial.println("t -> \t <-");
  Serial.println("f -> \f <-");
  Serial.println("\" -> \" <-");
  Serial.println("\' -> \' <-");
  Serial.println("\\ -> \\ <-");
  Serial.println("r -> \r <-");
  Serial.println("\  -> \  <-");
  Serial.println("AB -> \x41\x42  <-");
} 

int i = 0;

void loop() { 
  // nichts

 Serial.print("\r");
 Serial.print(i++,BIN);
 delay(200);
} 


