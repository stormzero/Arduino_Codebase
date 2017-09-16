#include <LiquidCrystal.h>

LiquidCrystal lcd2(1,2,3,4,5,6);

void setup() {
  // put your setup code here, to run once:\par

 Serial.begin(9600);
 lcd2.begin(16,4);

 Serial.println("<h1>This is a heading1 </h1>");
 Serial.println("<h2>This is a heading2 </h2>");
 Serial.println("<h3>This is a heading3 </h3>");
 Serial.println("<a href=\\"http:\\\\www.virtronics.com.au\\">Simulator page</a>");
 Serial.println("Line3!");
 lcd2.print("LCD test");
 lcd2.setCursor(0,1);
 lcd2.print("LCD Line2");
 lcd2.setCursor(0,2);
 lcd2.print("LCD Line3");
 lcd2.setCursor(0,3);
 lcd2.print("LCD Line4");

}

void loop() {
  // put your main code here, to run repeatedly:\par

}

