// Saved by Simulator for Arduino V0.98.B.4 refer to arduino.com.au
//Buzzer sounds everytime a key is pressed

const int LED0 = 12;
const int LED1 = 11;
const int LED2 = 10;
const int LED3 = 9;

const int BZR = 8;
const int LID = 13;

const int cols[3]={  
7,6,5};
const int rows[4]={  
4,3,2,1};

int key;
boolean pinOK;


void setup()
{
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT);  
  pinMode(LED3, OUTPUT); 

  pinMode(BZR, OUTPUT);
  pinMode(LID, INPUT);

  pinMode(rows[0], OUTPUT);
  pinMode(rows[1], OUTPUT);  
  pinMode(rows[2], OUTPUT);  
  pinMode(rows[3], OUTPUT);

  pinMode(cols[0], INPUT);
  pinMode(cols[1], INPUT);
  pinMode(cols[2], INPUT);
}


int keyscan()
{

  const int keys[12]={1,2,3,4,5,6,7,8,9,10,11,12  };
  int x,r,c,keypress=0;
  int ColState = 0;    //variable to store column state, 0 = low

  while(x=0)
  {
  for(r=0; r<4; r++)
  {
    digitalWrite(rows[r], HIGH);
    for(c=0;c<3;c++)
    {
      ColState =  digitalRead(cols[c]);
      if(ColState==1)goto keypressed;
    }
    digitalWrite(rows[r], LOW);
  }
  }

keypressed: 
  digitalWrite(rows[r], LOW);
  keypress = keys[(r*3)+c];
  return keypress;
}


boolean PINCHK()
{
  boolean PinRight = true;
  key = keyscan();
  if(key != 5)PinRight = false;
  key = keyscan();
  if(key != 6)PinRight = false;    
  key = keyscan();
  if(key != 7)PinRight = false;
  return PinRight;
}

void loop()
{
  digitalWrite(LED2, HIGH);
  pinOK = PINCHK();
  if(pinOK == true) 
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED0, LOW);
    tone(BZR, 1500, 500);
  }
  else
  {
    digitalWrite(LED0,HIGH);
        digitalWrite(LED1, LOW);
    tone(BZR, 400, 500);
  }
}










