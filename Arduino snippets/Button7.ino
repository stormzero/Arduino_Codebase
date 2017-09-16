                                                                     
                                                                     
                                                                     
                                             
//====================== Übung 2 ============================
byte Button=7;
byte LED=13;

boolean testB,testC;
boolean BIT=1;
boolean loop1=true;

void out(char d)
{
}

void setup()
{
  pinMode(Button,INPUT); pinMode(LED, OUTPUT);
char ch;
out(ch-'0'); // correct quote marks
//out(ch-‘0‘); // bad characters - rich text? 18 and 18
//out(ch-‘0’); // bad characters - rich text? 18 and 19 
}

void loop() 
{  
    testC = 0;
  testB = 1;
while(testB) {testB= digitalRead(Button);}         //--- wait for key press
  digitalWrite(LED,1); delay(500);
  digitalWrite(LED,0);     //--- Key pressed!  LED=on for 0.5s
  
  while(loop1)     //--- this is the main loop; loop forever..
  {
  testC=1; while(testB) {testB= digitalRead(Button);}         //--- wait for key press
  digitalWrite(LED,BIT);          //--- Key pressed!     update LED
  BIT=!BIT;            //--- toggle BIT
  delay(200);        //--- debounce
  }
  
}
 //==================================================================
