// Simulate(Uno) link sketch to Arduino board here

int a=0xff;
int sensorValue=1;
int c;
#define ENTER_SET_MODE_SHUNT 1
#define ENTER_SET_MODE_BRIGHT 2

int setTripPoint(int i)
{
	a = 3;
}

void setup() {
  // put your setup code here, to run once:
  if((sensorValue==ENTER_SET_MODE_SHUNT)
                           ||(sensorValue>=ENTER_SET_MODE_BRIGHT)) setTripPoint();
}

void loop() {
  // put your main code here, to run repeatedly:

}
