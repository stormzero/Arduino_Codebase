/* line 1
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
* Dolly Project
*
* Usa un LCD la motor shield FE, un motore bipolare
* tre pulsanti per la programmazione, 3 resistenze
*
* Da una idea di: Alfieri Mauro e LolloTek
* Lanternius 2012
*
*
*
*/
#include <LiquidCrystal.h>
// Input Analogici
int prev = A0;
int next = A1;
int conf = A2;
int pinPot = A3;
 
// Input Digitali Stepper
int motorPinDirA = 2;
int motorPinDirB = 8;
int motorPinPwmA = 3;
int motorPinPwmB = 9;
 
int nFase=1;
// Scatto
int pinLed = 13;          // uscita per lo scatto
int wakepin = 10;         // uscita per la messa a fuoco
 
int shutter_on = 200;     // tempo di pressione per attivare la cam, da settare intorno i 100 e 300
float shutter_on_sec = 0; // tempo di pressione per attivare la cam, da settare intorno i 100 e 300
int debound = 20;         // tempo di attesa pressione di un tasto
int shutter_off = 1500;   // tempo di attesa prima di attivare il motorino
 
int wakeup = 300;         // time to activate wakeup (focus)
int wakewait =200;        // time between wake and shutter
long  seconds;            // tempo di pausa tra gli scatti
 
// Menu Level
char* menu_principale[4] =  {"Settaggio","Controllo","Sposta Carrello","Avvio TimeLapse"};
char* submenu[4]          =  {"passi x scatto","Durata scatto","Numero scatti","Pausa tra scatti"};
 
// Init level
int ngiri=0, ii=0;
float interv=0;
int scatti=0;
int posizione=0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
void setup() {
 
  lcd.begin(16, 2);
  lcd.print("  Dolly Project ");
  lcd.setCursor(0, 1);
  lcd.print(" ALS 2012 v1.06 ");
  delay( 5000 );
  lcd.clear();
  lcd.print( menu_principale[posizione] ); // LINE 66
  digitalWrite( pinLed, LOW );
  pinMode(motorPinDirA, OUTPUT);
  pinMode(motorPinDirB, OUTPUT);
  pinMode(motorPinPwmA, OUTPUT);
  pinMode(motorPinPwmB, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(wakepin, OUTPUT);         //wakepin gives output
  pinMode(pinPot, INPUT);
  
}
void loop() {
  lcd.print( menu_principale[posizione] );
  lcd.setCursor(0, 1);
  int pnext = analogRead( next );
  int pprev = analogRead( prev );
  int pconf = analogRead( conf );
}
