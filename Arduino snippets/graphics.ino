// Simulate(Uno)
#include <Graphics.h>

Graphics gr(10,10,200,200,0xffffff,0xffffff);

#define RED 0xff
#define GREEN 0xff00
#define BLUE 0xff0000
#define PURPLE 0xff00ff
#define TEAL 0xffff00
#define YELLOW 0xffff
#define BLACK 0
#define WHITE 0xffffff


void setup() {
  // put your setup code here, to run once:
 gr.clear(BLACK);
 gr.line(10,10,30,20);
 gr.penWidth(5);
 gr.penColor(GREEN);
 gr.brushColor(BLUE);
 gr.line(60,10,80,20);
 gr.circle(50,50,10);
 gr.rectangle(60,60,100,30);
 gr.roundRect(40,100,115,45,10);
 gr.textColor(WHITE);
 gr.textSize(8);
 gr.text(30,30,"This is a test");
 gr.textSize(12);
 gr.text(30,50,"This is test2");
 for (int i=2; i<50; i++) {
   gr.pixel(i,2,YELLOW);
   gr.pixel(i,5,PURPLE);
 }


}

void loop() {
  // put your main code here, to run repeatedly:

}
