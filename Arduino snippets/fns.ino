// Saved by Simulator for Arduino V0.98.B.5 refer to arduino.com.au
// Saved by Simulator for Arduino V0.98.B.5 refer to arduino.com.au
// Simulate(Uno)

// Stimulus(test.sti)

int add(int i)
{
    return(i+25);
}

int i;

void setup() {
  // put your setup code here, to run once:
 i = 1;

}

void loop() {
  // put your main code here, to run repeatedly:
//    i = add(i+2);
//    i = add(i+2)+add(i);
//    i = add(add(i));
//  i = add(add(i+1)+add(i+2));

  if (add(i)>51)  {
      i = 1;
  }
  i += 25;
}
