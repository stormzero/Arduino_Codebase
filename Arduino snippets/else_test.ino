/*
// Saved by Simulator for Arduino V0.96.1.1
 Simulator for Arduino Test
 
 
*/

int Bubba   = 0;
int Gump    = 0;
int Shrimps = 0;

void setup(void)
{
}


// looping cycle
void loop()
{

  Bubba  = analogRead(A0);
  Gump   = analogRead(A1);

  if (Bubba > 511)
  {
    if (Gump > 511)
    {
      Shrimps = 1;
    }
    else
    {
      Shrimps = 0;
    }
  }
  else
  {
    Shrimps = 0;
  }


  if (Bubba > 511)
  {
    if (Gump > 511)
    {
      Shrimps = 1;
    }
    else
    {
      Shrimps = 0;
    }
  }
  else
  {
    Shrimps = 0;
  }

  // no clog
  delay(50);

}
