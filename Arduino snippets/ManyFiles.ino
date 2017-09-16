
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
//*********************************************************************
//
// INCLUDES
//
//*********************************************************************

#include <SoftwareSerial.h>

#include "ROV_Control.h"

#include "Serial.h"

#include "OneWire.h"

#include "TDCmp.h"

#include "Servo.h"

#include "Leak.h"

#include "Motor.h"

#include "ExtraSensors.h"

#include "Packet.h"

// DS18B20 Temperature sensors
// Use proprietary OneWire (tm) interface.
#include <OneWire.h>
// Definition of interrupt names
#include < avr/io.h >
// ISR interrupt service routine
#include < avr/interrupt.h >


//*********************************************************************
//
// SETUP
//
//*********************************************************************

void setup() {

TOP_SIDE_SERIAL.begin(115200);

pinMode(13,OUTPUT);
digitalWrite(13,LOW);
#ifdef LEAKS
pinMode(MCU_LEAK_SENSOR_DIGITAL_PIN, INPUT);
pinMode(MOTOR_LEAK_SENSOR_DIGITAL_PIN, INPUT);
//enableInterrupts();
#endif

pinMode(LIGHT_TRANSISTOR_CONTROL_PIN,OUTPUT);
digitalWrite(LIGHT_TRANSISTOR_CONTROL_PIN,LOW);
//setupSerial();

#ifdef TMPS
setupOneWire(ONE_WIRE_SETUP_TIMEOUT_MS);
#endif

#ifdef TDCMP
//validateTDCMP(TDCMP_SETUP_TIMEOUT_MS);
#endif

#ifdef SERVOS
setupServos();
#endif

#ifdef MOTORS
setupMotors();
#endif

#ifdef EXTRAS
setupExtraSensors();
#endif
}

boolean enableInterrupts(void) {

attachInterrupt(0, handleMcuLeak, RISING);
attachInterrupt(1, handleMotorLeak, RISING);

return true;
}


boolean setupServos(void) {

//LightServo.attach(LIGHT_SERVO_CONTROL_PIN);

//TiltServo.attach(TILT_SERVO_CONTROL_PIN);
}

boolean setupSerial(void) {

TOP_SIDE_SERIAL.begin(115200);
TOP_SIDE_SERIAL.flush();
//TDCMP_SERIAL.begin(115200);
//TDCMP_SERIAL.flush();

return true;
}

boolean setupOneWire(millisec_t timeOut) {

char message[100];
boolean failed = false;
boolean complete = false;
millisec_t limit = millis() + timeOut;
uint8_t state = 0;

while (millis() < limit)
{
switch (state) {
case 0:
failed = !setupOneWireAddresses();
break; 
case 1:
failed = !setupOneWireTypes();
break;
default:
complete = true;
break;
}

if (complete) {
break; 
}

if (!failed) {
state++; 
}
}

return failed;
}

//*********************************************************************
//
// OneWire
//
//*********************************************************************

char* identifySensor(DS18xxx_t *sensor, DS18xxx_op op) {

static byte externalAddr[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
static byte mcuAddr[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
//static byte motorsAddr[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
char* ret = (char*)DS18xxx_UNKNOWN;

if (op == DS18xxx_WRITE_EXTERNAL) {

copyAddr(sensor,externalAddr);

} else if (op == DS18xxx_WRITE_MCU) {

copyAddr(sensor,mcuAddr);

/*} else if (op == DS18xxx_WRITE_MOTORS) {

copyAddr(sensor,motorsAddr);
*/ 
} else {

//READ
if (compareAddr(sensor,externalAddr) == true) {

ret = (char*)DS18xxx_EXTERNAL;

} else if (compareAddr(sensor,mcuAddr) == true) {

ret = (char*)DS18xxx_MCU;

} /*else if (compareAddr(sensor,motorsAddr) == true) {

ret = (char*)DS18xxx_MOTORS;

}*/
}

return ret;
}

boolean compareAddr(DS18xxx_t *sensor, byte* buffer) {

boolean ret = true;
int i=0;

for (i=0; i<8; i++) {
if (sensor->addr[i] != buffer[i]) {
ret = false;
break;
}
}

return ret;
}

boolean copyAddr(DS18xxx_t *sensor, byte* buffer) {
int i=0;

for (i=0; i<8; i++) {
buffer[i] = sensor->addr[i];
}

return true;
}

uint8_t getTemperature(DS18xxx_t *sensor, char* buffer) {

byte i; 
byte data[12];
byte present = 0;
float celsius = 0;
char* id = (char*)DS18xxx_UNKNOWN;

sensor->controlLine->reset();
sensor->controlLine->select(sensor->addr);
sensor->controlLine->write(0x44,1); // start conversion, with parasite power on at the end

delay(ONE_WIRE_READ_TEMP_DELAY); // maybe 750ms is enough, maybe not
// we might do a ds.depower() here, but the reset will take care of it.

present = sensor->controlLine->reset();
sensor->controlLine->select(sensor->addr); 
sensor->controlLine->write(0xBE); // Read Scratchpad

id = identifySensor(sensor,DS18xxx_READ);

#ifdef VERBOSITY_2
DEBUG_PRINT(id);
#endif

#ifdef VERBOSITY_0
DEBUG_PRINT(" Data = ");
DEBUG_PRINT_T(present,HEX);
DEBUG_PRINT(" ");
#endif

for ( i = 0; i < 9; i++) { // we need 9 bytes
data[i] = sensor->controlLine->read();
#ifdef VERBOSITY_0
DEBUG_PRINT_T(data[i], HEX);
DEBUG_PRINT(" ");
#endif
}
#ifdef VERBOSITY_0
DEBUG_PRINT(" CRC=");
DEBUG_PRINT_T(OneWire::crc8(data, 8), HEX);
DEBUG_PRINTLN();
#endif

// convert the data to actual temperature

int16_t raw = (data[1] << 8) | data[0];

if (sensor->type == DS18S20) {
raw = raw << 3; // 9 bit resolution default
if (data[7] == 0x10) {
// count remain gives full 12 bit resolution
raw = (raw & 0xFFF0) + 12 - data[6];
}
} else {
byte cfg = (data[4] & 0x60);
if (cfg == 0x00) raw = raw << 3; // 9 bit resolution, 93.75 ms
else if (cfg ==) {}

}

void loop() {
  // put your main code here, to run repeatedly:

}
