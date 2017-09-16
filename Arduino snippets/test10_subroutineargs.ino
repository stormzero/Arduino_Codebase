
// Saved by Simulator for Arduino V0.98.B.3
// Saved by Simulator for Arduino V0.95B

float i1,i2;

void setup() {
  // put your setup code here, to run once:

}

int actual(int a)
{
    return(a);
}

float getit(int x)
{
 return(x+2.2);
}

float getit2(float a, float b)
{
 return ( a+b+3.3 );
}


void loop() {
  // put your main code here, to run repeatedly:

    if ((actual(6)>5) and (actual(7)>6)) {
        i1 = 1;
    }

    if ((actual(4)>5) and (actual(7)>6)) {
        i1 = 2;
    }

    if ((actual(6)>5) and (actual(5)>6)) {
        i1 = 3;
    }

    if ((actual(4)>5) and (actual(5)>6)) {
        i1 = 4;
    }


 i2 = getit2(3,getit(20));
 i1 = getit(5);
 i2 = getit2(3,4);

}
