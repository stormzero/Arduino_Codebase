
// Saved by Simulator for Arduino V0.96.0.2
// Saved by Simulator for Arduino V0.95B
int i,j;
#define XYZ 345

unsigned int check(unsigned int x)
{
 return x+5;
}

void setup() {
  // put your setup code here, to run once:
 i = XYZ;
}

void loop() {
  // put your main code here, to run repeatedly:

 j = check(i++);
}
