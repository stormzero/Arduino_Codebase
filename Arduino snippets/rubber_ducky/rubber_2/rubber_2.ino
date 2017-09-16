#include "DigiKeyboard.h"


void setup() 
{
DigiKeyboard.sendKeyStroke(KEY_ENTER);
DigiKeyboard.delay(6000);
}
void loop()
{
// this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:

}

