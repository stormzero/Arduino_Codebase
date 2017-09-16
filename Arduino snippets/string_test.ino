// Simulate(Uno) link sketch to Arduino board here

String s;
int i,j,k;
int sensorVal;

void setup() {
  // put your setup code here, to run once:

pinMode(13, HIGH);	
    sensorVal = 512;
float voltage = (sensorVal/1024.0) * 5.0;

    i = 12;
    j = 23;
    k = 34;
    s = String(123,DEC);
    s = String(54,HEX);
    s = String(5,BIN);
}

void loop() {
  // put your main code here, to run repeatedly:

}
