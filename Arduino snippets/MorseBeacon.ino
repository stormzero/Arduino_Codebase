/*
// Saved by Simulator for Arduino V0.97B
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.96.A.3
MorseBeacon
Ausgabe von Morsezeichen
*/
#define P 1
#define S 3
#define L 0


#define PIEZOAUSG 7
#define FREQ 800
#define KURZ 100
#define LANG 300
#define ZEICHENPAUSE 200
#define WORTPAUSE 1200

byte morsetabelle[10][6];
byte signal;
byte zeichenwert;
unsigned char zeichenindex;
unsigned char signalindex;


void setup()
{
  Serial.begin(9600);
  
  zeichenindex = 0;
  signalindex = 0;
  // Ablage Morsezeichen in Array
  //1 -> Punkt
  //3 -> Strich
  //0 -> keine Ausgabe
  morsetabelle[0][0] = S; // d
  morsetabelle[0][1] = P;
  morsetabelle[0][2] = P;
  morsetabelle[0][3] = L;
  morsetabelle[0][4] = L;
  morsetabelle[0][5] = L;
 
  morsetabelle[1][0] = S; // k
  morsetabelle[1][1] = P;
  morsetabelle[1][2] = S;
  morsetabelle[1][3] = L;
  morsetabelle[1][4] = L;
  morsetabelle[1][5] = L;
  
  morsetabelle[2][0] = P; // 4
  morsetabelle[2][1] = P;
  morsetabelle[2][2] = P;
  morsetabelle[2][3] = P;
  morsetabelle[2][4] = S;
  morsetabelle[2][5] = L;
  
  morsetabelle[3][0] = P; // a
  morsetabelle[3][1] = S;
  morsetabelle[3][2] = L;
  morsetabelle[3][3] = L;
  morsetabelle[3][4] = L;
  morsetabelle[3][5] = L;
  
  morsetabelle[4][0] = S; // q
  morsetabelle[4][1] = S;
  morsetabelle[4][2] = P;
  morsetabelle[4][3] = S;
  morsetabelle[4][4] = L;
  morsetabelle[4][5] = L;
  
  morsetabelle[5][0] = L; // Ende
  morsetabelle[5][1] = L;
  morsetabelle[5][2] = L;
  morsetabelle[5][3] = L;
  morsetabelle[5][4] = L;
  morsetabelle[5][5] = L;
}

void loop()
{
  signal = morsetabelle[zeichenindex][signalindex];
  
  // Erkennung Textende (alle Signalbits = 0)
  zeichenwert = // this line should be all on one row to work inthe simulator
    signal + 
    + morsetabelle[zeichenindex][signalindex + 1]
    + morsetabelle[zeichenindex][signalindex + 2]
    + morsetabelle[zeichenindex][signalindex + 3]
    + morsetabelle[zeichenindex][signalindex + 4]; 
 // zeichenwert = signal + morsetabelle[zeichenindex][signalindex + 1] + morsetabelle[zeichenindex][signalindex + 2]    + morsetabelle[zeichenindex][signalindex + 3]    + morsetabelle[zeichenindex][signalindex + 4];
    
  if(zeichenwert == 0)
  {
    // Ende des Zeichens
    // Start beim ersten Zeichen
    delay(WORTPAUSE);
    zeichenindex = 0;
    signalindex = 0;    
  }
  else
  {
    if(signal == P)
    {
     //Ausgabe Signal Punkt 
     tone(PIEZOAUSG,FREQ,KURZ);
     delay(KURZ);
     delay(KURZ);
     signalindex++;
    }
    else
    {
      if(signal == S)
      {
       //Ausgabe Signal Strich
       tone(PIEZOAUSG,FREQ,LANG);
       delay(LANG);
       delay(KURZ);
       signalindex++;
      }
      else
      {
        //keine weiteres Signal,
        //nächstes Zeichen
        delay(ZEICHENPAUSE);
        zeichenindex++;
        signalindex = 0;
      }
    }
  }

}
