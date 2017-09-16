// Simulate(Uno)
// Saved by Simulator for Arduino V0.97A


//#include <ServoTimer2.h>

const float perimeters[] PROGMEM = {
//const float perimeters[] = {
  0.79796, 0.87776, 0.95756, 1.03735, 1.11715, 1.19695, 1.27674, 1.35654, 1.43634, 
  1.51613, 1.59593, 1.67573, 1.75552, 1.83532, 1.91511, 1.99491, 2.07471, 2.1545, 
  2.2343, 2.3141
};

#typedef uint16_t prog_uint16_t;

//------------------------------------------ Master Sequence A -------------
const int Mas_A_Len = 1;
PROGMEM prog_uint16_t Array_Seq_GrprA[]  =  // Array_Seq_GrprA[Step][Unit 0-4]
{  
  0,0,0,0, 50,  //Turn off Engine #2
};

int z=0x1234;
int index = 3;
const float perim;
int Shrimps = 0;

float pgm_read_float(float *f)
{
 return(f);
}

int i,b;
int j=1;
float f1,g;

void setup() {
  // put your setup code here, to run once:

 i = j?4:123;

perim = 2.34;

 f1 = log10(100);
 g = log10(200); 

   Serial.begin(57600);
   Serial.println("Lizard Climate Control Starting Up...");

  // put your setup code here, to run once:
  perim = pgm_read_float(&perimeters[index]);
uint8_t a=z>>8;b =lowByte(z);
int Bubba   = 0;
int Gump    = 0;


  Bubba  = analogRead(A0);
  Gump   = analogRead(A1);

  if (Bubba > 511)
  {
    if (Gump > 511)
    {
      Shrimps = 1;
    }
    else
    {
      Shrimps = 0;
    }
  }
  else
  {
    Shrimps = 0;
  }
 Shrimps = 1;
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int x=0;x<100;x++)
    {
      if (x==10)
        {
          break;
        };
    };
 Shrimps = 2;

}
