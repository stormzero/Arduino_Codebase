
#include <avr/io.h>


/*Converts 8 bit Binary word to Decimal & Hex. */

void setup() {
 
 int b0=A0;int b1=A1;int b2 = get_b(2); int b3=A3;int 
b4=A4;; ; ;
     pinMode(A0,INPUT_PULLUP);pinMode(A1,INPUT_PULLUP);
}

   void loop() {
    int b0=A0;int b1=A1;int b2=A2;int b3=A3;int
    b4=A4; int b5=A5;;;
    byte b = MCUSR;
 
}

int get_b(int b)
{
    return b+2;
}


