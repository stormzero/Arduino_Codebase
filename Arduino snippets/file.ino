#define PortECHOPIN 9        // Pin to receive echo pulse - port
// Saved by Simulator for Arduino V0.98.A.2
#define PortTRIGPIN 8         // Pin to send trigger pulse - starboard
#define sBrdECHOPIN 7       // Pin to receive echo pulse
#define sBrdTRIGPIN 6        // Pin to send trigger pulse


int trig[] = {PortTRIGPIN, sBrdTRIGPIN}; // array of trigger pins
int echo[] = {PortECHOPIN, sBrdECHOPIN}; // array of detect echo pins

void setup() {
  // set up the Serial's number of columns and rows: 
  Serial.begin(9600);
  for(int i=0;i<2;i++){ 
    pinMode(echo[i], INPUT);
    pinMode(trig[i], OUTPUT);
  }
}
