{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\f0\fs16 // This sketch is provided as an instruction on various features of\par
// the Simulator for Arduino\par
\par
boolean b1 = FALSE;\par
char c = 'A';\par
byte b = 1;\par
int i = 2;\par
long l = 3L;\par
float f = 0.1;\par
String s = "Hi";\par
int j,k,m;\par
\par
\par
void setup() \{\par
// Simulate(Uno)\par
 i = 0;\par
// Resize the sketch window\par
// by holding right edge and dragging out\par
// to be wide to see all these comments, especially the line below.\par
// The cursor will be reset to the line above. Press F7 to step once\par
 i = 121;\par
// Now click the value in the middle list to change the value to 100\par
 if (i==100) \{\par
     pinMode(3,OUTPUT);\par
 \}\par
\par
/*// The code below shows how the Arduino boards can be changed \par
// from within the comments\par
// Simulate(Uno) */\par
 i = 1; // look at the right side\par
// Simulate(Due) \par
 i = 2;\par
// Simulate(Mega75)\par
 i = 3;\par
// Simulate(Uno)\par
 \par
// now right click in the variables window and select watch\par
// then single step below\par
 b1 = TRUE;\par
 c = 'A';\par
 b = 123;\par
 i = 256;\par
 l = 1234567L;\par
 f = 1.2345;\par
 s = "Hello There";\par
// now hover the mouse over each variable\par
\par
  for (i=0; i<3; i++) \{ // now select View Call Stack to watch the levels\par
     for (j=0; j<2; j++) \{\par
         for (k=0; k<2; k++) \{\par
             m = 0;\par
             while (m<1) \{\par
               m++;\par
             \}\par
         \}\par
     \}\par
  \}\par
\par
  Serial.begin(9600); // note the IO window autmatically opens\par
\par
\par
 i = 0;j = 0;\par
\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
    Serial.print(i++);\par
    Serial.print(",");\par
    Serial.println(++j);\tab\par
// now click edit and add your own line of code below\par
\par
\}\par
\par
}
 