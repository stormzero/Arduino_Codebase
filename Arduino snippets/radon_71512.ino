/*
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.96
  Christopher Nafis
  Written Jan 2012
  Read Radon values off SafetySiren Radon Gas Detector model HS80002
  Copyright 2012, Chris Nafis
*/

int debug = 1;


// modified the orig to have the segments all saved for later printing.
//
// removed orig initiation to fix them for a simulation session
// with what I am actually getting, in order to step thru code
// digits reads live 3.5
/*
int segments[] = {
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
};
*/
int segments[] = {
  0,1,0,0,1,0,0,
  1,1,1,1,1,1,1,
  1,1,0,0,1,1,0,
  0,0,0,0,1,0,0,
};

int leddigits[] = {
  1,1,1,1,1,1,1, // space
  1,1,1,0,0,0,1, // L
  0,0,0,0,0,0,1, // 0
  1,0,0,1,1,1,1, // 1
  0,0,1,0,0,1,0, // 2
  0,0,0,0,1,1,0, // 3
  1,0,0,1,1,0,0, // 4
  0,1,0,0,1,0,0, // 5 or S
  0,1,0,0,0,0,0, // 6
  0,0,0,1,1,1,1, // 7
  0,0,0,0,0,0,0, // 8
  0,0,0,1,1,0,0 // 9
};

char ledvalues[11] = " L0123456789";
// added 4 for simulator issue?
char leddisp[4] = "    ";

int i = 0;
int j = 0;
int found = 0;
int ledvaluecnt = 0;

unsigned long duration;

void setup() {
  Serial.begin(9600);
  // analog inputs are by default inputs. removed in debugging issues
  //pinMode(A0, INPUT); // Digit 4 strobe
  //pinMode(A1, INPUT); // Digit 3 strobe
  //pinMode(A2, INPUT); // digit 2 strobe
  //pinMode(A3, INPUT); // digit 1 strobe
  pinMode(2, INPUT); // Segment A
  pinMode(3, INPUT); // Segment B
  pinMode(4, INPUT); // Segment C
  pinMode(5, INPUT); // Segment D
  pinMode(6, INPUT); // Segment E
  pinMode(7, INPUT); // Segment F
  pinMode(8, INPUT); // Segment G
}

void loop() {

  //chnged orig to move all calculations until after data gathering.
  
  /*
     Digit 1
   */
  duration = pulseIn(A3, LOW);

  segments[0] = digitalRead(2);
  segments[1] = digitalRead(3);
  segments[2] = digitalRead(4);
  segments[3] = digitalRead(5);
  segments[4] = digitalRead(6);
  segments[5] = digitalRead(7);
  segments[6] = digitalRead(8);
  
  /*
   Digit 2
   */
  duration = pulseIn(A2, LOW);

  segments[7] = digitalRead(2);
  segments[8] = digitalRead(3);
  segments[9] = digitalRead(4);
  segments[10] = digitalRead(5);
  segments[11] = digitalRead(6);
  segments[12] = digitalRead(7);
  segments[13] = digitalRead(8);

 /*
   Digit 3
   */
   duration = pulseIn(A1, LOW);

  segments[14] = digitalRead(2);
  segments[15] = digitalRead(3);
  segments[16] = digitalRead(4);
  segments[17] = digitalRead(5);
  segments[18] = digitalRead(6);
  segments[19] = digitalRead(7);
  segments[20] = digitalRead(8);

 /*
   Digit 4
   */
   duration = pulseIn(A0, LOW);

  segments[21] = digitalRead(2);
  segments[22] = digitalRead(3);
  segments[23] = digitalRead(4);
  segments[24] = digitalRead(5);
  segments[25] = digitalRead(6);
  segments[26] = digitalRead(7);
  segments[27] = digitalRead(8);


  
  ledvaluecnt = 0;
  for (i = 0; i < sizeof(leddigits)/sizeof(int); i = i+7)
  {
    found = 1;
    for (j = 0; j < 7; j++)
    {
      if (segments[j] != leddigits[i+j]){
        found = 0;
        break;
      }
    }
    if (found == 1)
    {
      leddisp[0] = ledvalues[ledvaluecnt];
       if (leddisp[0] != ' ')
      {
        Serial.print(leddisp);
        break;
      }
      else
        Serial.print('?');
      break;
    }

    ledvaluecnt++;
  } 
  ledvaluecnt = 0;
  for (i=0;i<sizeof(leddigits)/sizeof(int);i=i+7)
  {
    found = 1;
    for (j=0;j<7;j++)
    {
      if (segments[j+7] != leddigits[i+j]){
        found = 0;
        break;
      }
    }
    if (found == 1)
    {
      leddisp[1] = ledvalues[ledvaluecnt];
      if (leddisp[1] != ' ')
      {
        Serial.print(leddisp);
 //       break;
      }
      else
        Serial.print('?');
 //       break;
  //    }
    ledvaluecnt++;
  }
    ledvaluecnt = 0;
  for (i=0;i<sizeof(leddigits)/sizeof(int);i=i+7)
  {
    found = 1;
    for (j=0;j<7;j++)
    {
      if (segments[j+14] != leddigits[i+j]){
        found = 0;
        break;
      }
    }
    if (found == 1)
    {
      leddisp[2] = ledvalues[ledvaluecnt];
      if (leddisp[2] != ' ')
      {
        Serial.print(leddisp);
        break;
      }
      else
        Serial.print('?');
      break;
    }
    
    ledvaluecnt++;
  }
    ledvaluecnt = 0;
  for (i=0;i<sizeof(leddigits)/sizeof(int);i=i+7)
  {
    found = 1;
    for (j=0;j<7;j++)
    {
      if (segments[j+21] != leddigits[i+j]){
        found = 0;
        break;
      }
    }
    if (found == 1)
    {
      leddisp[3] = ledvalues[ledvaluecnt];
      if (leddisp[3] != ' ')
      {
        Serial.println(leddisp);
        break;
      }
      else
        Serial.println('?');
      break;  
    }
    ledvaluecnt++;
  }
    if(debug == 1)
  {
    Serial.println("Debug, Digit 1 = ");
    Serial.print(" Seg A = ");
    Serial.println(segments[0]);
    Serial.print(" Seg B = ");
    Serial.println(segments[1]);
    Serial.print(" Seg C = ");
    Serial.println(segments[2]);
    Serial.print(" Seg D = ");
    Serial.println(segments[3]);
    Serial.print(" Seg E = ");
    Serial.println(segments[4]);
    Serial.print(" Seg F = ");
    Serial.println(segments[5]);
    Serial.print(" Seg G = ");
    Serial.println(segments[6]);

    Serial.println("Debug, Digit 2 = ");
    Serial.print(" Seg A = ");
    Serial.println(segments[7]);
    Serial.print(" Seg B = ");
    Serial.println(segments[8]);
    Serial.print(" Seg C = ");
    Serial.println(segments[9]);
    Serial.print(" Seg D = ");
    Serial.println(segments[10]);
    Serial.print(" Seg E = ");
    Serial.println(segments[11]);
    Serial.print(" Seg F = ");
    Serial.println(segments[12]);
    Serial.print(" Seg G = ");
    Serial.println(segments[13]);

    Serial.println("Debug, Digit 3 = ");
    Serial.print(" Seg A = ");
    Serial.println(segments[14]);
    Serial.print(" Seg B = ");
    Serial.println(segments[15]);
    Serial.print(" Seg C = ");
    Serial.println(segments[16]);
    Serial.print(" Seg D = ");
    Serial.println(segments[17]);
    Serial.print(" Seg E = ");
    Serial.println(segments[18]);
    Serial.print(" Seg F = ");
    Serial.println(segments[19]);
    Serial.print(" Seg G = ");
    Serial.println(segments[20]);

    Serial.println("Debug, Digit 4 = ");
    Serial.print(" Seg A = ");
    Serial.println(segments[21]);
    Serial.print(" Seg B = ");
    Serial.println(segments[22]);
    Serial.print(" Seg C = ");
    Serial.println(segments[23]);
    Serial.print(" Seg D = ");
    Serial.println(segments[24]);
    Serial.print(" Seg E = ");
    Serial.println(segments[25]);
    Serial.print(" Seg F = ");
    Serial.println(segments[26]);
    Serial.print(" Seg G = ");
    Serial.println(segments[27]);
  }
  delay(60000);
}















