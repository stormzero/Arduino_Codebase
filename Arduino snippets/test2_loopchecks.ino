// Simulate(Mega75)
// Saved by Simulator for Arduino V0.97
// Saved by Simulator for Arduino V0.96.A.3

long fd = 34;
int y = 23 ;
byte currentLED;
int direction;
int a, b,c,d,e,f;
int lowSpeed = 50;
int midSpeed = 150;
int highSpeed = 255;
int currentSpeed = lowSpeed;
int i;

void setup() {

  goto label_check;

 digitalWrite(10,y) ;

label_check:



                a = 5;
                b = 12;
                c = 17;
                d = 30;


    y = random();
    y = random(100);
    y = random(3000,4000);

    for (i=0; i<=53; i++) { 
        pinMode(i,OUTPUT);
        digitalWrite(i,HIGH);

        if ( digitalRead(d0)==0) {
            break;
        } 
    }

    digitalWrite(15,LOW);
    digitalWrite(9, FALSE );
}

void loop() 
{
  int counter=0; 

    while (i<7) i++;
    i = 0;
    i = 2<<4;
    i = 16%3;

    counter=0;

    do { 
        digitalWrite(counter, 0); // code beyond here is never executed if this is a For loop
        digitalWrite(counter, 1); // code beyond here is never executed if this is a For loop
        counter++;
    } while(counter<8) ; // hangs here in while loop

    for (counter=0; counter<8; counter++)
    { 
        digitalWrite(counter, 1); // code beyond here is never ever ever executed
        digitalWrite(counter, 0);
    }

 currentLED += direction;  // increment by the direction value
 // change direction if we reach the end
 if (currentLED == 9) {direction = -1;}
 if (currentLED == 0) {direction = 1;}

                if (a == b )
                                {
                                e = f;
                                }

  if(currentSpeed == 50)
  {
   currentSpeed = midSpeed;
  }
  else if(currentSpeed == 150)
  {
   currentSpeed = highSpeed;
  }
  else if(currentSpeed == 255)
  {
   currentSpeed = lowSpeed;
  }
  else
  {
   Serial.println("ERROR Speed not defined");
  }

}
