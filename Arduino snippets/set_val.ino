{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier;}}
\viewkind4\uc1\pard\f0\fs16 #define position 20\par
// Saved by Simulator for Arduino V0.98A\par
// Saved by Simulator for Arduino V0.98\par
word someSensor[position];\par
byte i;\par
word total;\par
word average;\par
int _i_1;\par
\par
// Stimulus(test.sti)\par
\par
void setup() \par
\{\par
\par
\}\par
\par
void loop()\par
\{\par
\par
for (i = 0; i < position; i++)\par
\{\par
total = total - someSensor[i];\par
someSensor[i] = analogRead(0);\par
total = total + someSensor[i];\par
average = total / position;\par
\}\par
\}\par
\par
}
 