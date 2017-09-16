/*global values*/
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2
const int analogInPin = A0;  //analog input pin what I can use to effect the programming
int analogOutPin = 11; // Analog out can be any of the pins mirked with a "~" PWM
float fullWaveRectified;
const float pi=3.14;
int outputValue = 0;
/*assighn integers*/
float x=0;
int yMax = 5, yMin = 0;
float y;

void setup()
{
  Serial.begin(9600); // this block starts serial communication through the usb so value can be displayed on the computer
}
void loop()
{
/*This for loop will cycle through all values of x and generate a sine wave at 1/10 resolution.*/
for (x=0;x<=100;x=x+.01)
{
  y=sin(pi*x)*128+128;
  //y=y+x;
  analogWrite(analogOutPin,fullWaveRectified); //sends pwm value to analogOutpin
  fullWaveRectified=y;//abs(y);
  //The following serial.print statements are used to output the data to the computer
  {Serial.print("Value of (x,y) abs(y)");  Serial.print("(");  Serial.print(x);  Serial.print(",");  Serial.print(y);  Serial.print(") abs("); Serial.print(fullWaveRectified); Serial.print(")\n");}
  delay(50);
 if(y<0)
 {
   //Serial.print("point");
   //delay(1000);
 }
}
x=0;
y=y*x;
}/*
int xOld=0;
for(x=0;x<=255;x++)
{
  y=x;
  print y;
  if(x<=xOld)
  for(;x>=0;x--)
  {
    y=x;
    print y;
  }
  else
  xOld=x;
}*/
