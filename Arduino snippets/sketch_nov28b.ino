#include <SD.h>
#include <Wire.h>
//#include "RTClib.h"

//RTC_DS1307 RTC;
int Decade = 0;
int Anno = 2012;
int Mese = 3;
int Giorno = 11;
int Ore = 6;
int Minuti = 1;
int Secondi = 25;
const int chipSelect = 10;
int i=0;

void setup()
{
  //seriale aperta a 9600 baud
  Serial.begin(9600);
  Serial.println("Initializing SD card...");

  //inizializziamo i pin 3 e 4 per i led rosso-verde
  //pin 10 riservato al card reader
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 

  //se il modulo sd non viene correttamente inizializzato
  if (!SD.begin(chipSelect)) {
    //messaggio di errore sul nostro monitor seriale
    Serial.println("Card failed, or not present");

    for (i=0;i<10;i++) {
      //blinking del led rosso
      digitalWrite(3, HIGH);   
      delay(100);              
      digitalWrite(3, LOW);     
      delay(100);
    }
    return;
  }

  //se correttamente inizializzata...
  Serial.println("card initialized.");
  //blinking led verde
  digitalWrite(4, HIGH);   
  delay(500);              
  digitalWrite(4, LOW);

  //inizializziamo l'RTC
  Wire.begin();
  //RTC.begin();
  /*if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }*/
}

void loop()
{
  //chiediamo il tempo all'RTC
  //DateTime now = RTC.now();
  int analogPin=0;
  int sensor =0;  

  //aspettiamo 3secondi
  delay(2900);

  //leggiamo e convertiamo la temperatura dal pin 0 di arduino
  sensor = analogRead(analogPin);
  sensor = (5.0 * sensor * 100.0)/1024.0;

  //stampa sulla seriale
  Serial.print("Temperatura: ");
  Serial.println(sensor);

  //apriamo in scrittura il file sulla sd
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  //Scriviamo: TEMPERATURA - ORA:MINUTI:SECONDI
  if (dataFile) {
    dataFile.print(sensor);
    dataFile.print(" - ");
    dataFile.print(Ore, DEC);
    dataFile.print(":");
    dataFile.print(Minuti, DEC);
    dataFile.print(":");
    dataFile.println(Secondi, DEC);
    //chiudiamo il file
    dataFile.close(); 

    //blinking led verde
    digitalWrite(4, HIGH);   
    delay(100);              
    digitalWrite(4, LOW);
  }  
  else {

    //errore nell'apertura del file o card rimossa
    Serial.println("error opening datalog.txt");
    for (i=0;i<10;i++) {
      //blinkig led rosso
      digitalWrite(3, HIGH);   
      delay(100);              
      digitalWrite(3, LOW);     
      delay(100);
    }
  } 
}
