{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24      \par
 #include<avr/wdt.h>                                                                \par
                                  \par
                                                     \par
                       \par
                      \par
//====================== \'dcbung 2 ============================\par
byte Button=7;\par
byte LED=13;\par
\par
boolean testB,testC;\par
boolean BIT=1;\par
boolean loop1=true;\par
\par
void setup()\par
\{\par
  pinMode(Button,INPUT); pinMode(LED, OUTPUT);\par
wdt_enable(WDT0_8S);\par
\}\par
\par
void loop() \par
\{  \par
  testB = 1;while(testB) \{testB= digitalRead(Button);\}         //--- wait for key press\par
  digitalWrite(LED,1); delay(500);\par
  digitalWrite(LED,0);     //--- Key pressed!  LED=on for 0.5s\par
  \par
  while(loop1)     //--- this is the main loop; loop forever..\par
  \{\par
  testC=1; while(testB) \{testB= digitalRead(Button);\}         //--- wait for key press\par
  digitalWrite(LED,BIT);          //--- Key pressed!     update LED\par
  BIT=!BIT;            //--- toggle BIT\par
  delay(200);        //--- debounce\par
  \}\par
  \par
\}\par
 //==================================================================\par
\par
}
 