{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 // Simulate(Uno) link sketch to Arduino board here\par
#include <LiquidCrystal.h>\par
// SimulateLCD(39,50,480,163,3,4,8388608,16777215,16711680)\par
\par
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);\par
\par
int i,curr_temp=234;\par
long l;\par
unsigned long ul;\par
// Simulate1LCD(39,50,480,103,4,5,8388608,16777215,16711680)// x,y,w,h,pixel w,p-p,blit_color,oncolor,offcolor width=6*lcdx*p-p height=10*lcdy*p-p\par
// change Simulate1LCD to SimulateLCD () to show LCD\par
\par
const byte test[8][3] = \{\{\{0,0,0\},\{0,0,0\},\{0,0,0\},\{0,0,0\},\{0,0,0\},\{0,0,0\},\{0,0,0\},\{0,0,0\}\}\};\par
\par
void setup() \{\par
  // put your setup code here, to run once:\par
#if (1)\par
    for (i=0;i<2;i++) \{\par
            l = 23;\par
    \}\par
    l=34;\par
\par
    l = 4294967295; // this line should error and set l to -1\par
    l = 2147483648; // this line should error and set l to -2147...\par
    l--;\par
    ul = 4294967295;\par
    ul--;\par
    ul -=3;\par
    ul +=2;\par
    ul -=i;\par
    ul /=2;\par
    ul *=2;\par
#endif    \par
\par
    lcd.begin(20,4);\par
    lcd.print(millis()/1000); \par
    lcd.setCursor(2,3); \par
    lcd.print('O');\par
    lcd.setCursor(5,1); \par
    lcd.print(curr_temp);\par
    lcd.backlight(50);\par
    lcd.backlight(25);\par
    for (i=0; i<100; i+=5) \{\par
        lcd.backlight(100-i);\par
    \}\par
    for (i=0; i<=100; i+=5) \{\par
        lcd.backlight(i);\par
    \}\par
\}\par
\par
void loop() \{\par
  // put your main code here, to run repeatedly:\par
\par
\par
\}\par
\par
}
 