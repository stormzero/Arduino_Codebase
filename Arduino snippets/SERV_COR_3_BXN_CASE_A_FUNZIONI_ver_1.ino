
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
#define BUTTON1 6             // pin di input dove è collegato il pulsante
#define BUTTON2 7             // pin di input dove è collegato il pulsante
#define LED1 8                // LED collegato al pin digitale 8
#define LED2 9                // LED collegato al pin digitale 9
#define LCDLight 13           // Luce LCD collegata al PIN 13

// includere la libreria:

// Simulate(Uno_LCD_Reverse.txt)

#include <LiquidCrystal.h>
#include "Funzioni_esterne.ino"

/*
   Viene creata l'istanza dell'oggetto LiquidCrystal chiamata lcd in cui
   sono indicati i pin dell'LCD collegati alle uscite digitali di Arduino
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definizione dei prototipi

int  val1 = HIGH;        // si userà val per conservare lo stato del pin di input
int  val2 = HIGH;
int radio=0;

int lungh_coda=2000; // Lunghezza della coda in mS <----------------------------------------------

int radio_attiva_1();
int radio_attiva_2();

void setup() {
  //impostiamo il numero di colonne ed il numero di righe di lcd
  lcd.begin(16, 2);
  // Visualizzo il messaggio sul display
  //lcd.print("SER Vallescr BXN");
  
  pinMode(LCDLight, OUTPUT);
  pinMode(LED1, OUTPUT);       // imposta il pin digitale come output
  pinMode(BUTTON1, INPUT);     // imposta il pin digitale come input
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON2, INPUT);
  
}

void loop() {
  // posiziona il cursore in colonna 0 e linea 1
  // (nota: la linea 1 e la seconda linea, poichè si conta incominciando da 0):
  //lcd.setCursor(0, 1);
  // Visualizzo il messaggio sul display


// legge il valore dell'input e lo conserva

  val1 = digitalRead(BUTTON1);  
  val2 = digitalRead(BUTTON2);
  
// carico il valore del pulsante premuto nella variabile radio

  if (val1==HIGH) {  
    radio=1;
  
  }  
  if (val2==HIGH) {  
    radio=2;
  }
  
 
// Sceglie in base a quale tasto è stato premuto quale radio attivare
 
 switch (radio) 
    { 
      
     
        case 1: 
            radio_attiva_1();
        break;
  
    
        case 2: 
            radio_attiva_2();        
        break;    
 
    }

// sbianco la variabile radio che altrimenti conserverebbe il valore corrente rientrando nel ciclo di loop

// radio=0;

lcd.setCursor(0, 0);
lcd.print("SER BXN fnz ver1");

lcd.setCursor(0, 1);
lcd.print("    STAND BY    ");

// inizio cazzate mie per portare a display i contenuti delle variabili e capire

  //lcd.setCursor(0, 0);
  //lcd.print(radio);
    //lcd.setCursor(3, 0);
    //lcd.print(val1);
    //lcd.setCursor(6, 0);
    //lcd.print(val2);
    
// lcd.setCursor(0, 1);
// lcd.print("    STAND BY    ");

 
 // fine cazzate mie per portare a display i contenuti delle variabili e capire
 
 }
 



