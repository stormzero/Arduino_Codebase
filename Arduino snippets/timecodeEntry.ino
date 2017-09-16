// Simulate(Uno)
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2
// Saved by Simulator for Arduino V0.97.B.2

unsigned long timer;
int timecodeEntry[4];
int timebase;
long frames1;

void setup()
{
      Serial.begin(9600);        // for comms to the programming PC

}
void loop()
{

 timebase = 1;

/*frames1 = (((timecodeEntry[0]>>4) * 10 * 60 * 60 * timebase) +
       ((timecodeEntry[0] & 0xf) * 60 * 60  * timebase) +
       ((timecodeEntry[1]>>4) * 10 * 60 * timebase) +
       ((timecodeEntry[1] & 0xf) * 60  * timebase) +
       ((timecodeEntry[2]>>4) * 10 * timebase) +
       ((timecodeEntry[2] & 0xf) * timebase) +
       ((timecodeEntry[3]>>4) * 10) +
       (timecodeEntry[3] & 0xf); */
    frames1 = 
       ((timecodeEntry[2] & 0xf) * timebase) +
       ((timecodeEntry[3]>>4) * 10) +
       (timecodeEntry[3] & 0xf); 
Serial.print(timer);
       Serial.println(" ");

}


