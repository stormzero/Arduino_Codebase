// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A

//----------------------------------------------------------------
//Include

//#include <Servo.h> 

//----------------------------------------------------------------
//Constant

const byte priorityRatio[3] = {5,5,0};
const byte elapsedTime = 0;
const byte currentTime = 1;
const byte lastTime =2;


//----------------------------------------------------------------
//Variable
 
unsigned long priority0Time[3];
unsigned long priority1Time[3];
unsigned long priority2Time[3];
unsigned long priority20msTime[3];
unsigned long priority100msTime[3];
unsigned long priority1sTime[3];
unsigned long priority10sTime[3];

 
//----------------------------------------------------------------
void setup() 

  {
  priority0Time[currentTime]=micros();
  priority1Time[currentTime]=micros();
  priority2Time[currentTime]=micros();
  priority20msTime[currentTime]=micros();
  priority100msTime[currentTime]=micros();
  priority1sTime[currentTime]=micros();
  priority10sTime[currentTime]=micros();
  }

//----------------------------------------------------------------
void loop() 
 
  {
  for (int p12Count=1; p12Count < priorityRatio[1]; p12Count++)
    { 
    for (int p01Count=1; p01Count < priorityRatio[0]; p01Count++)
      {

      runPriority0();
      }
    runPriority1();
    runPriority20ms();
    runPriority100ms();
    }
  runPriority2();
  runPriority1s();
  runPriority10s();
  }

//----------------------------------------------------------------
unsigned long elapsedTimeCalculator (unsigned long currentTimeL, unsigned long lastTimeL)

  {
  unsigned long elapsedTimeL;
  
  if (currentTimeL >= lastTimeL)
    {
    elapsedTimeL = currentTimeL-lastTimeL;
    }
  else
    {
    elapsedTimeL = 4294967295 - lastTimeL;
    elapsedTimeL = elapsedTimeL + currentTimeL;
    }
  return elapsedTimeL;
  }

//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority0 ()

  {
  elapsedTimePriority0Calculator(&priority0Time[lastTime], &priority0Time[currentTime], &priority0Time[elapsedTime]);
  inputPriority0();
  processPriority0();
  outputPriority0();
  }

//----------------------------------------------------------------
void elapsedTimePriority0Calculator (unsigned long *lastTimeA, unsigned long *currentTimeA, unsigned long *elapsedTimeA)

  {
  *lastTimeA = *currentTimeA;
  *currentTimeA = micros();
  *elapsedTimeA = elapsedTimeCalculator (*currentTimeA, *lastTimeA);
  }
  
//----------------------------------------------------------------
void inputPriority0 () 

  {
  // Priority0 inputs here
  }

//----------------------------------------------------------------
void processPriority0 ()  

  {

  }
//----------------------------------------------------------------
void outputPriority0 ()  

  {

  }

//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority1 ()

  {
  elapsedTimePriority1Calculator();
  inputPriority1();
  processPriority1();
  outputPriority1();
  }

//----------------------------------------------------------------
void elapsedTimePriority1Calculator ()

  {
  priority1Time[lastTime] = priority1Time[currentTime];
  priority1Time[currentTime] = micros();
  priority1Time[elapsedTime] = elapsedTimeCalculator (priority1Time[currentTime], priority1Time[lastTime]);
  }
 
//----------------------------------------------------------------
void inputPriority1 () 

  {
  
  }

//----------------------------------------------------------------
void processPriority1 ()  

  {

  }
//----------------------------------------------------------------
void outputPriority1 ()  

  {

  }
//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority2 ()

  {
  elapsedTimePriority2Calculator();
  inputPriority2();
  processPriority2();
  outputPriority2();
  }

//----------------------------------------------------------------
void elapsedTimePriority2Calculator ()

  {
  priority2Time[lastTime] = priority2Time[currentTime];
  priority2Time[currentTime] = micros();
  priority2Time[elapsedTime] = elapsedTimeCalculator (priority2Time[currentTime], priority2Time[lastTime]);
  }
 
//----------------------------------------------------------------
void inputPriority2 () 

  {
  
  }

//----------------------------------------------------------------
void processPriority2 ()  

  {

  }
//----------------------------------------------------------------
void outputPriority2 ()  

  {

  }
//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority20ms()

  {
  unsigned long cTime;
  cTime =elapsedTimeCalculator(micros(),priority20msTime[currentTime]);
  if ((cTime>=20000)
    {
    elapsedTimePriority20msCalculator();
    inputPriority20ms();
    processPriority20ms();
    outputPriority20ms();
    }
  }

//----------------------------------------------------------------
void elapsedTimePriority20msCalculator ()

  {
  priority20msTime[lastTime] = priority20msTime[currentTime];
  priority20msTime[currentTime] = micros();
  priority20msTime[elapsedTime] = elapsedTimeCalculator (priority20msTime[currentTime], priority20msTime[lastTime]);
  }
 
//----------------------------------------------------------------
void inputPriority20ms () 

  {
  
  }

//----------------------------------------------------------------
void processPriority20ms ()  

  {

  }

//----------------------------------------------------------------
void outputPriority20ms ()  

  {

  }

//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority100ms()

  {
  unsigned long cTime;
  cTime =elapsedTimeCalculator(micros(),priority100msTime[currentTime]);
  if ((cTime>=100000)
    {
    elapsedTimePriority100msCalculator();
    inputPriority100ms();
    processPriority100ms();
    outputPriority100ms();
    }
  }

//----------------------------------------------------------------
void elapsedTimePriority100msCalculator ()

  {
  priority100msTime[lastTime] = priority100msTime[currentTime];
  priority100msTime[currentTime] = micros();
  priority100msTime[elapsedTime] = elapsedTimeCalculator (priority100msTime[currentTime], priority100msTime[lastTime]);
  }
 
//----------------------------------------------------------------
void inputPriority100ms () 

  {
  
  }

//----------------------------------------------------------------
void processPriority100ms ()  

  {

  }

//----------------------------------------------------------------
void outputPriority100ms ()  

  {

  }

//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority1s()

  {
  unsigned long cTime;
  cTime =elapsedTimeCalculator(micros(),priority1sTime[currentTime]);
  if ((cTime>=1000000)
    {
    elapsedTimePriority1sCalculator();
    inputPriority1s();
    processPriority1s();
    outputPriority1s();
    }
  }

//----------------------------------------------------------------
void elapsedTimePriority1sCalculator ()

  {
  priority1sTime[lastTime] = priority1sTime[currentTime];
  priority1sTime[currentTime] = micros();
  priority1sTime[elapsedTime] = elapsedTimeCalculator (priority1sTime[currentTime], priority1sTime[lastTime]);

  }
 
//----------------------------------------------------------------
void inputPriority1s () 

  {
  
  }

//----------------------------------------------------------------
void processPriority1s ()  

  {

  }
//----------------------------------------------------------------
void outputPriority1s ()  

  {

  }

//----------------------------------------------------------------
//----------------------------------------------------------------
void runPriority10s()

  {
  unsigned long cTime;
  cTime =elapsedTimeCalculator(micros(),priority10sTime[currentTime]);
  if ((cTime>=10000000)
    {
    elapsedTimePriority10sCalculator();
    inputPriority10s();
    processPriority10s();
    outputPriority10s();
    }
  }

//----------------------------------------------------------------
void elapsedTimePriority10sCalculator ()

  {
  priority10sTime[lastTime] = priority10sTime[currentTime];
  priority10sTime[currentTime] = micros();
  priority10sTime[elapsedTime] = elapsedTimeCalculator (priority10sTime[currentTime], priority10sTime[lastTime]);
  }
 
//----------------------------------------------------------------
void inputPriority10s () 

  {
  
  }

//----------------------------------------------------------------
void processPriority10s ()  

  {

  }

//----------------------------------------------------------------
void outputPriority10s ()  

  {

  }

//----------------------------------------------------------------


