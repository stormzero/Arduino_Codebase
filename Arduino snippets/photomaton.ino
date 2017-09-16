#include <Bounce.h>
// Déclaration des ports utilisés
// Entrées digitales
int in_BoutonVert = 2;
int in_BoutonBleu = 3;

// Sorties digitales
int out_LED_bleu = 4;
int out_LED_vert = 5;
int out_Eclairage = 6;
int out_Occupation = 7;
int out_LED_ruban = 8;


// Utilisé pour la gestion des commandes reçues par le port série
char incomingByte;                        
boolean start_msg = false;
String buffer_in = "";
String received_command="";
String msg_to_send="";


// Gestion des boutons
Bounce bouncer_vert = Bounce(in_BoutonVert,2); 
boolean gblnBoutonVert=false;
Bounce bouncer_bleu = Bounce(in_BoutonBleu,3); 
boolean gblnBoutonBleu=false;

// Pour clignotement
int intLedState = LOW;             // ledState used to set the LED
unsigned long lngCurrentMillis = millis();
long lngPreviousMillis = 0;        // will store last time LED was updated
long lngInterval = 1000;           // interval at which to blink (milliseconds)
boolean blnLedBoutonVertON = false;
boolean blnRubanON = false;


// Divers
int intEtatActuel = 0;
// 0=enclenchement et attente client
// 1=pressé bouton vert, et en attente possibilité presser bouton bleu
// 2=bouton bleu activé
// 3=prises de vues en cours
// 4=en cours impression

void setup()
{   
  pinMode(in_BoutonVert, INPUT);   
  digitalWrite(in_BoutonVert, HIGH);       // turn on pullup resistor
  pinMode(in_BoutonBleu, INPUT);   
  digitalWrite(in_BoutonBleu, HIGH);       // turn on pullup resistor
  pinMode(out_LED_bleu, OUTPUT);   
  digitalWrite(out_LED_bleu,LOW);   
  pinMode(out_LED_vert, OUTPUT);   
  digitalWrite(out_LED_vert,HIGH); 
  pinMode(out_Eclairage, OUTPUT);   
  digitalWrite(out_Eclairage,LOW); 
  pinMode(out_Occupation, OUTPUT);   
  digitalWrite(out_Occupation,LOW); 
  pinMode(out_LED_ruban, OUTPUT);   
  digitalWrite(out_LED_ruban,LOW); 
  
  Serial.begin(9600);
}

void loop()
{
  
  // Actions en fonctions des divers état de fonctionnement
  if (intEtatActuel == 0) {
    digitalWrite(out_Occupation,LOW); 
    digitalWrite(out_Eclairage,LOW);
    digitalWrite(out_LED_ruban,LOW);
    blnLedBoutonVertON=true;
    blnRubanON=false;
    // Gestion pression du bouton vert
      if (bouncer_vert.update()) {
        if (gblnBoutonVert) {
          gblnBoutonVert=false;
        } 
        else {
          gblnBoutonVert=true;
        }
      }  
      
      if (gblnBoutonVert) {
         intEtatActuel == 1; 
      }
  }


  if (intEtatActuel == 1) {
    gblnBoutonVert=false;
    digitalWrite(in_BoutonVert, LOW);
    digitalWrite(out_Occupation,HIGH);
    digitalWrite(out_Eclairage,HIGH); 
         
  }
  
  
  if (intEtatActuel == 2) {
    digitalWrite(out_LED_bleu, HIGH); 
    // Gestion pression du bouton bleu
    if (bouncer_bleu.update()) {
      if (gblnBoutonBleu) {
        gblnBoutonBleu=false;
      } 
      else {
        gblnBoutonBleu=true;
      }
    }
      if (gblnBoutonBleu) {
         intEtatActuel == 3; 
      }
  }

  if (intEtatActuel == 3) {
    digitalWrite(out_LED_bleu, LOW);
    gblnBoutonBleu=false;
  }


  if (intEtatActuel == 4) {
    blnRubanON=true;  
  }



  // Lecture du port sériel
  if (Serial.available() > 0)
  {
    // read the incoming byte from Line Scanner:
    incomingByte = char(Serial.read());
    //Serial.print(incomingByte);

    if (incomingByte == '+') //reset
    {
      start_msg=false;
      buffer_in = "";
      received_command="";
    } 

    if (incomingByte == '<') 
    {               
      start_msg=true;
      buffer_in = "";
      received_command="";
    } 
    else {
      if (start_msg == true) 
      {
        if (incomingByte == '>') 
        {
          received_command=buffer_in;
          ExecuteCommand();
          start_msg=false;
        } 
        else {
          buffer_in=buffer_in + incomingByte;
        }
      }
    }
  }
  
  // Gestion du clignotement led bouton vert + ruban LED sortie photos
  if(lngCurrentMillis - lngPreviousMillis > lngInterval) {
    // save the last time you blinked the LED
    lngPreviousMillis = lngCurrentMillis;  

    // if the LED is off turn it on and vice-versa:
    if (intLedState == LOW) {
      intLedState = HIGH;
    }
    else {
      intLedState = LOW;
    }

    if (blnLedBoutonVertON==true) {
      digitalWrite(out_LED_vert, intLedState);
    }
    else {
      digitalWrite(out_LED_vert, LOW);      
    }
    if (blnRubanON==true) {
      digitalWrite(out_LED_ruban, intLedState);
    }
    else {
      digitalWrite(out_LED_ruban, LOW);      
    }
  }
}

void ExecuteCommand() {
  Serial.print("Execute:" + received_command + " ");

  if (received_command == "STA") SendStatut(); // demande de statut
  if (received_command == "RST") { // État initial
      intEtatActuel=0;
  }
  if (received_command == "BLE") { // En attente bouton bleu
      intEtatActuel=2;
  }

  if (received_command == "PHO") { // En cours de prises de vues
      intEtatActuel=3;
  }

  if (received_command == "PRT") { // En cours d'impression
      intEtatActuel=4;
  }
}


void SendStatut() {   
  Serial.print("<");
  Serial.print(gblnBoutonVert);
  Serial.print(",");
  Serial.print(gblnBoutonBleu);
  Serial.print(">");
}


