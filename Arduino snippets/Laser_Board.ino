
// Saved by Simulator for Arduino V0.97A
// Saved by Simulator for Arduino V0.97A
// Analog input declaration
const int in_Power_15 = A0;  // Analog input monitor pin attached to +/-15V power supply 
const int in_Power_12 = A1;  // Analog input monitor pin attached to +/-12V power supply 
const int in_Power_24 = A2;  // Analog input monitor pin attached to +/-24V power supply 

// Digital output declaration
const int out_Power_12 = 22; // Digital pin to control 12V power supply relay
const int out_Power_24 = 23; // Digital pin to control +/-24V power supply relay
const int out_Power_Green = 24; // Digital pin to control green power supply relay
const int out_Power_TEC1 = 25; // Digital pin to control TEC 1 power relay
const int out_Power_TEC2 = 26; // Digital pin to control TEC 2 power relay

// Constant declaration
const float Power_15_expected = 4.0; 
const float Power_12_expected = 4.0; 
const float Power_24_expected = 4.0; 


//***************************************************************************************************************************

void setup()
{
 pinMode(out_Power_12, OUTPUT);
 pinMode(out_Power_24, OUTPUT);
 pinMode(out_Power_TEC1, OUTPUT);
 pinMode(out_Power_TEC2, OUTPUT);
 pinMode(out_Power_Green, OUTPUT);
 //serial.begin(9600);
}

void loop()
{
boolean power_ok=0;
boolean Power12=0;
boolean Power15=0;
boolean Power24=0;

do 
{
 Power15=power_good_startup(in_Power_15);
 Power12=power_good_startup(in_Power_12);
 Power24=power_good_startup(in_Power_24);
 power_ok=Power12&&Power15&&Power24;
} while (!power_ok);
}

// Function to check stability of a power source at startup
// read analog value from a pin and check against expected voltage
// value on analog pin is between 0-5V => use voltage divider for voltage over 5V
// check only positive values or use AOP inverter for negative one
// takes 5 samples and check if there's less than 1% difference from expected voltage

boolean power_good_startup (int Power_Name) { 
float voltage_moy=0.0;
float min_voltage=0.0;
float max_voltage=0.0;
float voltage_expected=0.0;
// Check power voltage based on its name
switch(Power_Name) {
 case in_Power_15:
  voltage_expected = Power_15_expected;
 break;
 case in_Power_12:
  voltage_expected = Power_12_expected;
 break;
 case in_Power_24:
  voltage_expected = Power_24_expected;
 break;
}

//Convert voltage expected (from 0...5V to 0...1023) and calculate min & max accepted
min_voltage= voltage_expected*(1023.0/5.0)*0.995;
max_voltage= voltage_expected*(1023.0/5.0)*1.005;

// take 5 sample during 500ms
for (int x=0;x<5;x++){
 voltage_moy = voltage_moy + (float)analogRead(Power_Name);
 delay(100);
}

// calculate average voltage
voltage_moy= voltage_moy/5.0;

//check if the value is acceptable range of 1%
if ((voltage_moy<min_voltage)||(voltage_moy>max_voltage))
{
 return 0;
} 
else
{
 return 1;
} 
}

// Function to check stability of a power source
// read analog value from a pin and check against expected voltage is within 5% range
// value on analog pin is between 0-5V => use voltage divider for voltage over 5V
// check only positive values or use AOP inverter for negative one
// return the number of error, reset to 0 the counter if no error found
// check on the number of error count must be handle in the main loop

int power_good (int Power_Name, int error_count) { 
float voltage=0.0;
float min_voltage=0.0;
float max_voltage=0.0;
float voltage_expected=0.0;
// Check power voltage based on its name
switch(Power_Name) {
 case in_Power_15:
  voltage_expected = Power_15_expected;
 break;
 case in_Power_12:
  voltage_expected = Power_12_expected;
 break;
 case in_Power_24:
  voltage_expected = Power_24_expected;
 break;
}

//Convert voltage expected (from 0...5V to 0...1023) and calculate min & max accepted
min_voltage= voltage_expected*(1023.0/5.0)*0.975;
max_voltage= voltage_expected*(1023.0/5.0)*1.025;

// Read Power supply output value
voltage = (float)analogRead(Power_Name);

//check if the value is acceptable range of 5%
if ((voltage<min_voltage)||(voltage>max_voltage))
{
 error_count++;
 return  error_count; 
} 
else
{
 return 0;
} 
}


