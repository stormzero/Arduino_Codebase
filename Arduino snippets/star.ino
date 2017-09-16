// Saved by Simulator for Arduino V0.98D refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98D refer to vitronics.com.au
// Simulate(Leonardo) link sketch to Arduino board here
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98
// Saved by Simulator for Arduino V0.98

// SerialIn(abc\n);

char  i;
char star = '*';
boolean BTAvailable = true;
void setup() {
 // put your setup code here, to run once:
 Serial1.begin(9600);
}

void loop() {
 // put your main code here, to run repeatedly:
 while (Serial1.available()> 0 && BTAvailable) {
  i  = (char)Serial1.read();
  Serial1.print(i);
     if (i == '*')
     {
       Serial1.print('Star');
     }
    
 }
}
