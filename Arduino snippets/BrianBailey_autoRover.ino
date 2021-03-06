{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 /*\par
// Saved by Simulator for Arduino V0.96.A.3\par
* Brian Bailey *\par
* Drives servo robot and avoids obsticles using Sharp IR range finder\par
* http://bunedoggle.com/robots.php\par
*/\par
#define CENTER 1400\par
#define CENTER_R CENTER\par
#define CENTER_L CENTER+1\par
\par
#define LEFT CENTER-650\par
#define RIGHT CENTER+650\par
\par
#define R_FULL_FORWARD R_STOP+300\par
#define L_FULL_FORWARD L_STOP-300\par
#define L_FULL_REVERSE R_FULL_FORWARD\par
#define R_FULL_REVERSE L_FULL_FORWARD\par
#define R_STOP 1450\par
#define L_STOP 1450\par
\par
#define LEFT_TURN 0\par
#define RIGHT_TURN 1\par
#define QUARTER_TURN_DELAY 800 // in milliseconds\par
\par
#define DIST_ERR 50\par
\par
#define RSPEED R_STOP + 100\par
#define LSPEED L_STOP - 110\par
\par
#define DEBUG 0\par
\par
#define BUMP_DELAY 125\par
\par
int leftDist = 0; // the average\par
int rightDist = 0;\par
int forDist = 0;\par
int vision = 5;\par
boolean goingLeft = true;\par
boolean turnNow = false;\par
\par
int curDist = 0;\par
int objDist = 0;\par
int objDir = 0;\par
\par
//#include <ServoTimer2.h>\par
#include <Servo.h>\par
\par
#define ServoTimer2 Servo\par
\par
// create servo objects to control servos\par
ServoTimer2 leftWheel;\par
ServoTimer2 rightWheel;\par
ServoTimer2 head;\par
\par
int leftSpeed = LSPEED; // variable to store the servo position\par
int rightSpeed = RSPEED;\par
int headPos=CENTER;\par
\par
void setup()\par
\{\par
leftWheel.attach(10); // attaches the servo on pin 9 to the servo object\par
rightWheel.attach(11);\par
head.attach(9);\par
\par
rightWheel.write(rightSpeed); // Stop Wheels\par
leftWheel.write(leftSpeed); // Stop Wheels\par
head.write(headPos);\par
\par
Serial.begin(9600); // initialize serial communication with computer\par
\}\par
\par
/*******************************************************\par
* turn - Executes an in-place turn for miliseconds\par
* QUARTER_TURN_DELAY gets you about 90 deg\par
********************************************************/\par
void turn(int dir, int duration)\{\par
// Store previous speeds\par
//rightSpeed = rightWheel.read();\par
//leftSpeed = leftWheel.read();\par
\par
if(dir == LEFT_TURN)\{\par
rightWheel.write(R_FULL_REVERSE);\par
leftWheel.write(L_FULL_FORWARD);\par
\}\par
else \{\par
rightWheel.write(R_FULL_FORWARD);\par
leftWheel.write(L_FULL_REVERSE);\par
\}\par
delay(duration);\par
\par
// restore previous speeds\par
rightWheel.write(rightSpeed);\par
leftWheel.write(leftSpeed);\par
\}\par
\par
void go()\{\par
rightWheel.write(RSPEED);\par
leftWheel.write(LSPEED);\par
\}\par
\par
void stop()\{\par
rightWheel.write(R_STOP);\par
leftWheel.write(L_STOP);\par
\}\par
\par
/***************************************************\par
* scan - This function is called every cycle\par
* it turns the head a click and records a distance and\par
* heading. It only saves the closest object info.\par
* objDist and objDir hold the closest object data\par
****************************************************/\par
void scan()\{\par
\par
if(goingLeft)\{\par
head.write(head.read()-10);\par
\}\par
else\{\par
head.write(head.read()+10);\par
\}\par
\par
if(head.read() <= LEFT)\{\par
goingLeft = false;\par
forDist = 0;\par
objDist = 0;\par
turnNow = true;\par
\}\par
\par
if(head.read() >= RIGHT)\{\par
goingLeft = true;\par
forDist = 0;\par
objDist = 0;\par
turnNow = true;\par
\}\par
\par
curDist = analogRead(vision);\par
if(curDist > objDist)\{\par
objDist = curDist;\par
objDir = head.read();\par
if(DEBUG)\{\par
Serial.print("\'9dNew close obj at Dist: ");\par
Serial.print(objDist);\par
Serial.print("\'9d heading: ");\par
Serial.println(objDir);\par
\}\par
\}\par
\par
delay(10);\par
\par
\}\par
\par
/**********************************************************\par
* bump\par
* Executes a nudge to a given side\par
* Pass in LEFT_TURN or RIGHT_TURN\par
***********************************************************/\par
void bump(int dir)\{\par
#define BUMP 100\par
if(dir == LEFT_TURN)\{\par
rightWheel.write(rightWheel.read()-BUMP);\par
delay(BUMP_DELAY);\par
rightWheel.write(rightWheel.read()+BUMP);\par
\}\par
else \{\par
leftWheel.write(leftWheel.read()+BUMP);\par
delay(BUMP_DELAY);\par
leftWheel.write(leftWheel.read()-BUMP);\par
\}\par
\}\par
\par
/**********************************************************\par
* bumpSteer\par
* Nudges us back on coarse if we see something off to the\par
* side. Relies on objDist and objDir to be updated by scan()\par
*\par
***********************************************************/\par
void bumpSteer()\{\par
// One bump per scan\par
if(!turnNow || objDist < 470)\par
return;\par
\par
if(objDir > CENTER)\{\par
bump(RIGHT_TURN);\par
\}\par
else if(objDir <= CENTER)\{\par
bump(LEFT_TURN);\par
\}\par
// No turn till next scan\par
turnNow = false;\par
\}\par
\par
void lookAround()\{\par
head.write(LEFT);\par
delay(400);\par
leftDist = analogRead(vision);\par
head.write(CENTER);\par
delay(400);\par
forDist = analogRead(vision);\par
head.write(RIGHT);\par
delay(400);\par
rightDist = analogRead(vision);\par
head.write(CENTER);\par
delay(200);\par
\}\par
\par
int cornerNav()\{\par
if(objDist > 600 && objDir > CENTER - 350 && objDir < CENTER + 200)\{\par
\par
if( DEBUG )\{\par
Serial.println("Check:");\par
Serial.println(objDist);\par
Serial.println(objDir);\par
\}\par
\par
stop();\par
lookAround();\par
if(leftDist > rightDist + DIST_ERR)\{\par
turn(LEFT_TURN, QUARTER_TURN_DELAY);\par
\}\par
else \{\par
turn(RIGHT_TURN, QUARTER_TURN_DELAY);\par
\}\par
go();\par
objDist = 0;\par
return 1;\par
\}\par
return 0;\par
\}\par
\par
void loop()\par
\{\par
\par
scan();\par
if(!cornerNav())\{\par
bumpSteer();\par
\}\par
\par
\}\par
\par
}
 