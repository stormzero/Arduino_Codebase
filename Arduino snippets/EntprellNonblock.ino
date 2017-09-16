// MotorRichtung
//Programm zur Ein/Ausschaltung des Motors in zwei 
//Richtungen, AUS und AUS mit Bremse */

/* Pinbelegung */
/*L289, C:5, D:7, EN:6 */
#define PIN_C 5
#define PIN_D 4
#define PIN_EN 6
//Taste
#define PIN_TASTE 7
// Entprellzeit Taste in ms
#define ENTPRELLZEIT (unsigned long)100

#define TASTE_NICHTBETAETIGT 1
#define TASTE_BETAETIGT 0

// Deklaration Variablen
boolean tastwert = TASTE_NICHTBETAETIGT; // aktueller Tastenwert
boolean tastwert_alt = TASTE_NICHTBETAETIGT; // Tastenwert vor Flanke
boolean taster_flag = false; // Flanke einmal erkannt
boolean taste_erkannt = false; // Taste entprellt
unsigned long time_alt; // startzeit der Entprellung
unsigned long time; // Aktuelle Zeit

void setup()
{
 Serial.begin(9600);
 pinMode(PIN_TASTE,INPUT);
 pinMode(8,OUTPUT);
}

void loop()
{


  
  taste_erkannt = false;
  /* Laeuft gerade eine Entprellung ? */
  if(taster_flag == true)
  {
    /*Ja, Aktuellen Zeitwert einlesen*/
    time = millis();
    /* Entprellzeit abgelaufen ?*/
    Serial.print("t_akt ");
    Serial.print(time);
    Serial.print(" t_alt ");
    Serial.println(time_alt);
    
    if (time > (time_alt + ENTPRELLZEIT))
    {
       /* Taste noch betätigt ? */
      if(tastwert == TASTE_BETAETIGT)
      {
        /* Ja, Tastenwert gueltig */
        taste_erkannt = true;
        /* Entprellung erfolgreich beendet */
        taster_flag = false;
        Serial.println("Taste erkannt");
      }
      else
      {
        /* Taste wird als nicht entprellt erkannt*/
        taste_erkannt = false;
        /* Entprellung abgebrochen */
        taster_flag = false;
      }
    }
  }
  else
  {
    /* Wird neue Flanke an Taste erkannt ?*/
    tastwert = digitalRead(PIN_TASTE);

    if((tastwert == TASTE_BETAETIGT) && (tastwert_alt == TASTE_NICHTBETAETIGT) == 1)
    {
      /* Entprellung starten */
      taster_flag = true;
      time_alt = millis(); 
    }
    tastwert_alt = tastwert;
  }
 

      
  if(taste_erkannt == true)
  {
    tone(8,1000,1000);
  }
}
