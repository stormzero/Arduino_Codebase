//=====================================================================================================

#define BRISKET 0
#define BUTT 1

#if BRISKET
#define GRILL_OFF_MEAT_TEMP   175
#define MEAT_FINISHING_TEMP   190
#define INITIAL_GRILL_TEMP    250      // Temp for the first hours of the smoke :)
#define SECONDARY_GRILL_TEMP  225      // Finishing temp of the smoke.
#define HOURS_TRIGGER          48      // Set to a large number (i.e. 48) if you don't want to trigger on time.
#define FOOD_TEMP_TRIGGER     150      //  Food temp to trigger SECONDARY_GRILL_TEMP state
#endif

#if BUTT
#define GRILL_OFF_MEAT_TEMP   200 
#define MEAT_FINISHING_TEMP   200
#define INITIAL_GRILL_TEMP    235      // Temp for the first hours of the smoke :)
#define SECONDARY_GRILL_TEMP  265      // Finishing temp of the smoke.
#define HOURS_TRIGGER           5      // Set to a large number (i.e. 24) if you don't want a secondary temp.
#define FOOD_TEMP_TRIGGER     500      //  Food temp to trigger SECONDARY_GRILL_TEMP state
#endif


//  The Chef does not touch anything below this line
//======================================================================================================

#define FAN_CONTROL_PIN 3       // PWM pin 3

#define GRILL_PROBE_PIN 0        // Analog pin 0
#define FOOD_PROBE_1_PIN 1      // Analog pin 1
#define FOOD_PROBE_2_PIN 2
#define FOOD_PROBE_3_PIN 3

#define PHASE_1_LED_PIN  09
#define PHASE_2_LED_PIN  10
#define PHASE_3_LED_PIN  11
#define PHASE_4_LED_PIN  12
#define DONE_LED_PIN     13


void setup() {   

  //printf("Hello\n");
  pinMode(FAN_CONTROL_PIN, OUTPUT);    // init fan pin
  
  Serial.begin(57600);
}

enum state {
  GRILL_INIT=3,
  GRILL_PHASE_1,        
  GRILL_PHASE_2,
  GRILL_OFF,
  MEAT_FINISHING,
  FINISHED
};

enum state MyState = GRILL_INIT;

void loop() 
{
  static int desiredGrillTemp=0;

    Serial.print("Timer = ");  Serial.print((float)millis()/(1000.0*60.0*60.0));  Serial.print("\n");
    Serial.print("State = ");  Serial.print(MyState);  Serial.print("\n");
    Serial.print("desiredGrillTemp = ");  Serial.print(desiredGrillTemp);  Serial.print("\n");
    Serial.print("GRILL Probe = ");Serial.print(getTemp(GRILL_PROBE_PIN));Serial.print(", ");
    Serial.print("Food Probes 1-3 = ");Serial.print(getTemp(FOOD_PROBE_1_PIN));  Serial.print(", "); Serial.print(getTemp(FOOD_PROBE_2_PIN));   Serial.print(", "); 
    Serial.print(getTemp(FOOD_PROBE_3_PIN));  
    Serial.print("\n");


  switch (MyState){
    
    case GRILL_INIT:
      setFanDutyCycle(0);                  // turn fan off
      MyState = GRILL_PHASE_1;
      return;
      break;
      
    case GRILL_PHASE_1:
      desiredGrillTemp = INITIAL_GRILL_TEMP;
      
                                              // If we reach the first phase time trigger
      if ( ((float)millis() / (60.0*60.0*1000.0)) >= HOURS_TRIGGER){
        MyState = GRILL_PHASE_2;
        return;
      }
                                              //  If we reach the first phase meat temp trigger
      if ( (getTemp(FOOD_PROBE_1_PIN) >= FOOD_TEMP_TRIGGER) && (getTemp(FOOD_PROBE_2_PIN) >= FOOD_TEMP_TRIGGER) ){
        MyState = GRILL_PHASE_2;
        return;
      }
      break;
      
    case GRILL_PHASE_2:
      desiredGrillTemp = SECONDARY_GRILL_TEMP;
      break;
      
    case GRILL_OFF:          
                            // SEND TEXT MSG - Light LED indicating "Time to Wrap in Foil !!!"
      setFanDutyCycle(0);
      desiredGrillTemp = 150;
      MyState = MEAT_FINISHING;
      return;
      break;
      
    case MEAT_FINISHING:
                            // Light LED !!!!!!
      if ( (getTemp(FOOD_PROBE_1_PIN) >= MEAT_FINISHING_TEMP) && (getTemp(FOOD_PROBE_2_PIN) >= MEAT_FINISHING_TEMP) ){
        MyState = FINISHED;
      }
      return;
      break;
      
    case FINISHED:
                            // Light LED !!!!!!
      return;
      break;  
  }
  
  
                                          // Check to see if BOTH probes are above GRILL_OFF_MEAT_TEMP
  if ( (getTemp(FOOD_PROBE_1_PIN) >= GRILL_OFF_MEAT_TEMP) && (getTemp(FOOD_PROBE_2_PIN) >= GRILL_OFF_MEAT_TEMP) ){
    MyState = GRILL_OFF;                     // SHUT'ER DOWN !!!!!!!  Get the tongs out !
    return;
  }
          // Set the necessary fan duty cycle
   setFanDutyCycle( (desiredGrillTemp - getTemp(GRILL_PROBE_PIN)) *12 );  // 1 degree below -> run fan @ 10%,   10 degrees below - run fan @ 100%
   
   if (desiredGrillTemp - getTemp(GRILL_PROBE_PIN) > 15 ){
                                                               // TEXT MSG and flash all LED's
     Serial.print("Grill > 15 degrees below temp !! - Add charcoal and reignite if necessary\n"); 
   }

  return;
}



void setFanDutyCycle(int percentage)
{
  int dutyCycle = percentage * 1.9 + 65;
  
  if (percentage <= 0){
    analogWrite(FAN_CONTROL_PIN, 0);
  }
  else {
    if (percentage >= 100){
      analogWrite(FAN_CONTROL_PIN, 255);
    }
    else{
      analogWrite(FAN_CONTROL_PIN, dutyCycle);
    }
  }
  
  Serial.print("dutyCycle = ");
  Serial.print(percentage);
  Serial.print("% -> ");
  Serial.print(dutyCycle);
  Serial.write("\n");
}



#define NUM_SAMPLES 5
#define SAMPLE_INTERVAL 250
float getTemp(int pin){
  float valueSum=0;
  float value;
  float Temp;
 
  for (int i=0; i<NUM_SAMPLES; i++){      // Sample and average to smooth drift
    valueSum = valueSum + analogRead(pin);
    delay(SAMPLE_INTERVAL);
  } 
  
  value = valueSum / NUM_SAMPLES;
    
  Temp = log(((10240000/value) - 10000));
  Temp = 1 / (0.001275726585 + (0.0001060475358 + (0.0000002372757464 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

  return Temp;
}

