// Simulate(Uno) link sketch to Arduino board here

int i;
  String D = "loop0";

void setup()
{
  String D = "loop1"; 
 Serial.begin(9600);
 

 
    i = test(i);
  Demo(D);
  Serial.print("D=");
  Serial.println(D);
}
 
void loop()
{
  Serial.print("D=");
  Serial.println(D);
}
 
int Demo(String D)
{
  D="loop2";
  return 0;
}

int test(int i)
{
    return(i+5);
}

