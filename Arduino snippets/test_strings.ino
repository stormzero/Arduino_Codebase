// Simulate Uno
// Saved by Simulator for Arduino V0.96.A.2

int i1 = 12;
int i2 = 34;
int i3 = 56;
String StringMessaggio ;

void MenuPrincipale()
{
//  menuAttivo = 3; 
 // PulisciLCD();

//  tempoTotale     = secondiPasso * quantiPassi;

//  lcd.setCursor(0, 0);
  
  StringMessaggio = (String)i3 + "[passi] " + (String)i1 + "[min]";
  
  Serial.println(StringMessaggio);
//  lcd.setCursor(0, 1);
  
  StringMessaggio = (String)i1 + "[mm] ogni " + (String)i2 + "[sec]";
  
  Serial.println(StringMessaggio);
 // Serial.setCursor(0, 2);
  Serial.println("1. Imposta parametri");
 // Serial.setCursor(0, 3);
  Serial.println("2. Avvia");
//  Serial.setCursor(0, 0);
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 MenuPrincipale();

}

void loop() {
  // put your main code here, to run repeatedly:

}
