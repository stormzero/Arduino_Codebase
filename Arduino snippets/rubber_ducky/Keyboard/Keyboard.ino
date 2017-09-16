#include "DigiKeyboard.h"

void setup() {
  // don't need to set anything up to use DigiKeyboard
}


void loop() {
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  

DigiKeyboard.sendKeyStroke(0,MOD_GUI_LEFT);// windows key or linux super

  DigiKeyboard.delay(300);
  DigiKeyboard.println("terminal");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(450);
  DigiKeyboard.println("netdiscover");
  //DigiKeyboard.delay(100);
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
 DigiKeyboard.sendKeyStroke(KEY_ENTER);
 //DigiKeyboard.delay(300);
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  DigiKeyboard.delay(10000);
  //DigiKeyboard.sendKeyStroke(0);
}
