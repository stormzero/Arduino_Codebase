{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 /*PID Library\par
// Saved by Simulator for Arduino V0.95D\par
// Saved by Simulator for Arduino V0.95D\par
// Saved by Simulator for Arduino V0.95B\par
/********************************************************\par
 * PID Basic Example\par
 * Reading analog input 0 to control analog PWM output 3\par
 ********************************************************/\par
\par
#include <PID_v1.h>\par
\par
//Define Variables we'll be connecting to\par
double Setpoint, Input, Output;\par
\par
//Specify the links and initial tuning parameters\par
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);\par
\par
void setup()\par
\{\par
  //initialize the variables we're linked to\par
  Input = analogRead(0);\par
// test comment\par
\par
  Setpoint = 100;\par
\par
  //turn the PID on\par
  myPID.SetMode(AUTOMATIC);\par
\}\par
\par
void loop()\par
\{\par
  Input = analogRead(0);\par
  myPID.Compute();\par
  analogWrite(3,Output);\par
\}\par
\par
}
 