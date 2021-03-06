{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Saved by Simulator for Arduino V0.98D refer to vitronics.com.au\par
\par
#include <DualMC33926MotorShield.h>\par
#include <avr/io.h>\par
\par
DualMC33926MotorShield md;\par
 \par
void stopIfFault()\par
\{\par
  if (md.getFault())\par
  \{\par
    Serial.println("fault");\par
    while(1);\par
  \}\par
\}\par
 \par
void setup()\par
\{\par
  Serial.begin(115200);\par
  Serial.println("Dual MC33926 Motor Shield");\par
  md.init();\par
\}\par
 \par
void loop()\par
\{\par
  for (int i = 0; i <= 400; i++)\par
  \{\par
    md.setM1Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M1 current: ");\par
      Serial.println(md.getM1CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
   \par
  for (int i = 400; i >= -400; i--)\par
  \{\par
    md.setM1Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M1 current: ");\par
      Serial.println(md.getM1CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
   \par
  for (int i = -400; i <= 0; i++)\par
  \{\par
    md.setM1Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M1 current: ");\par
      Serial.println(md.getM1CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
 \par
  for (int i = 0; i <= 400; i++)\par
  \{\par
    md.setM2Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M2 current: ");\par
      Serial.println(md.getM2CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
   \par
  for (int i = 400; i >= -400; i--)\par
  \{\par
    md.setM2Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M2 current: ");\par
      Serial.println(md.getM2CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
   \par
  for (int i = -400; i <= 0; i++)\par
  \{\par
    md.setM2Speed(i);\par
    stopIfFault();\par
    if (abs(i)%200 == 100)\par
    \{\par
      Serial.print("M2 current: ");\par
      Serial.println(md.getM2CurrentMilliamps());\par
    \}\par
    delay(2);\par
  \}\par
\}\par
\par
}
 