/*
// Saved by Simulator for Arduino V0.97.B.2
 Version 10-04-2012
 Copyright 2012 Max Ritter, George Rhoten

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

//Adjust the following pin values when neccesary
//Left-Right Servo Pin
#define HORIZ_SERVO_PIN 9
//Up-Down Servo Pin
#define VERT_SERVO_PIN 8

//#include <avr/io.h>
#include "io.h"
#include <inttypes.h>
//#include <compat/twi.h>

/** defines the data direction (reading from SMBus device) in smb_start(),smb_rep_start() */
#define SMB_READ    1

/** defines the data direction (writing to SMBus device) in smb_start(),smb_rep_start() */
#define SMB_WRITE   0

/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
 
/* bus clock in Hz */
#define SCL_CLOCK 50000L

/**
 * Initialization of the SMBus interface. Need to be called only once
 * @param enablePullups Set to true to enable the internal pullups
 */
void smb_init(bool enablePullups) {
    if (enablePullups) {
        PORTC = (1 << PORTC4) | (1 << PORTC5); //Enabling Pull-Ups for the MLX90614
    }

    /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
    TWSR = 0;                         /* no prescaler */
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */
}

/**
 * Terminates the data transfer and releases the SMBus bus
 */
void smb_stop(void) {
    /* send stop condition */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    // wait until stop condition is executed and bus released
    while (TWCR & (1<<TWSTO)) {
    }
}

/**
 * Wait until previous transmission completed
 */
static inline void smb_waitForRelease(void) {
    while (!(TWCR & (1<<TWINT))) {
    }
}

/**
 * Send one byte to SMBus device
 * 
 * @param data The byte to be transfered
 * @return 0 write successful. 1 write failed
 */
uint8_t smb_write(uint8_t data) { 
    // Send data to the previously addressed device
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    smb_waitForRelease();

    // check value of TWI Status Register. Mask prescaler bits
    return ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK);
}

/**
 * Read one byte from the SMBus device, read is followed by a stop condition 
 *
 * @param arr The array to fill up.
 * @param len The length of the array and the amount to read.
 */
void smb_read(uint8_t *arr, int len) {
    // Leave room for the last byte.
    len--;
    for (int idx = 0; idx < len; idx++) {
        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
        smb_waitForRelease();
        arr[idx] = TWDR;
    }
    // Read last byte
    TWCR = (1<<TWINT) | (1<<TWEN);
    smb_waitForRelease();
    arr[len] = TWDR;
}

/**
 * Issue a start condition, and return the status of operation
 * @return 0 = device accessible, 1 = failed to access device
 */
static inline bool smb_startCondition() {
    // Send START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    smb_waitForRelease();

    // Check value of TWI status register. Mask prescaler bits.
    uint8_t retVal = TW_STATUS & 0xF8;
    return (retVal != TW_START) && (retVal != TW_REP_START);
}

/**
 * Write the address and transfer direction
 * @param address The address and transfer direction of SMBus device
 * @return The masked TW status
 */
static inline uint8_t smb_startWriteAddress(uint8_t address) {
    // Send device address
    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);
    smb_waitForRelease();

    // Check value of TWI Status Register. Mask prescaler bits.
    return TW_STATUS & 0xF8;
}

/**
 * Issues a start condition and sends address and transfer direction.
 * @param address The address and transfer direction of SMBus device
 * @return 0 = device accessible, 1= failed to access device
 */
bool smb_start(uint8_t address) {
    if (smb_startCondition()) {
        return 1;
    }

    uint8_t twst = smb_startWriteAddress(address);
    return ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK));
}

/**
 * Issues a start condition and sends address and transfer direction.
 * If device is busy, use ack polling to wait until device is ready
 * 
 * @param address Address and transfer direction of SMBus device
 */
void smb_startWait(uint8_t address) {
    for (;;) {
        if (smb_startCondition()) {
            continue;
        }

        uint8_t twst = smb_startWriteAddress(address);
        if ((twst != TW_MT_SLA_NACK) && (twst != TW_MR_DATA_NACK)) {
            break;
        }
        /* The device is busy. Send stop condition to terminate write operation */
        smb_stop();
    }
}

#include <Servo.h>
#include <EEPROM.h>

#define TEMP_OFFSET 27315
enum {
  TEMP_AMBIENT = 0x6,
  TEMP_OBJECT = 0x7
};

/*
This is the minimal amount of time in milliseconds required before the temperature value is updated.
Any less time will return the previous reading.
*/
#define MIN_READ_WAIT 125

/*
A raw temperature change larger than this requires more time for
the sensor to warm up or cool down for an accurate reading.
*/
#define MAX_SAFE_TEMPERATURE_CHANGE 50


long int count = 0;

int mlr = 1275; //Middle point for LR Servo; only used if there is no existing calibration
int mud = 1750; //Middle point for UD Servo; only used if there is no existing calibration
int blr = 1600; //Left-Bottom point for LR Servo; only used if there is no existing calibration
int bud = 1550; //Left-Bottom point for UD Servo; only used if there is no existing calibration
int lines = 48;
int rows = 64;

Servo lr; //Servo for left-right movement
Servo ud; //Servo for up-down movement

void setup(){ 
  Serial.begin(115200); //BaudRate for Serial Communication
  mlr = EEPROM.read(0)*10; //Read existing calibration from the EEPROM
  mud = EEPROM.read(1)*10;
  if(mlr == 0 || mud == 0){
    mlr = 1275; //Middle point for LR Servo; only used if there is no existing calibration
    mud = 1750; //Middle point for UD Servo; only used if there is no existing calibration
  }
  blr = EEPROM.read(2)*10;
  bud = EEPROM.read(3)*10;
  if(blr == 0 || bud == 0){
    blr = 1600; //Left-Bottom point for LR Servo; only used if there is no existing calibration
    bud = 1550; //Left-Bottom point for UD Servo; only used if there is no existing calibration
  }

  smb_init(true);
 
  ud.attach(VERT_SERVO_PIN); //Attach servos
  lr.attach(HORIZ_SERVO_PIN); 
  
  ud.writeMicroseconds(mud); //Move servos to middle position
  lr.writeMicroseconds(mlr);
}

void loop() {
    if (Serial.available() > 0) {
        switch (Serial.read()) {
        case 'a':
            measure();
            break;
        case 'b':
            middleleft();
            break;
        case 'c':
            middleright();
            break;
        case 'd':
            middleup();
            break;
        case 'e':
            middledown();
            break;
        case 'f':
            middlesave();
            break;
        case 'g':
            bottomleft();
            break;
        case 'h':
            bottomright();
            break;
        case 'i':
            bottomup();
            break;
        case 'j':
            bottomdown();
            break;
        case 'k':
            bottomsave();
            break;
        case 'l':
            gotoMiddle();
            break;
        case 'm':
            gotoBottomLeft();
            break;
        case 'n':
            res1();
            break;
        case 'o':
            res2();
            break;
        case 'p':
            res3();
            break;
        case 'q':
            res4();
            break;
        }
    }
}

void gotoMiddle() { //go to middle pos
    ud.writeMicroseconds(mud);
    lr.writeMicroseconds(mlr);
}
void gotoBottomLeft() { //go to bottom-left pos
    ud.writeMicroseconds(bud);
    lr.writeMicroseconds(blr);
}
void middleleft() { //move middle pos left
    mlr += 10;
    gotoMiddle();
}
void middleright() { //move middle pos right
    mlr -= 10;
    gotoMiddle();
}
void middleup() { // move middle pos up
    mud += 10;
    gotoMiddle();
}
void middledown() { //move middle pos down
    mud -= 10;
    gotoMiddle();
}
void bottomleft() { //move bottom-left pos left
    blr += 10;
    gotoBottomLeft();
}
void bottomright() { //move bottom-left pos right
    blr -= 10;
    gotoBottomLeft();
} 
void bottomup() { //move bottom-left pos up
    bud += 10;
    gotoBottomLeft();
}
void bottomdown() { //move bottom-left pos down
    bud -= 10;
    gotoBottomLeft();
}
void middlesave() { //save middle pos to EEPROM
    EEPROM.write(0,(mlr*0.1));
    EEPROM.write(1,(mud*0.1));
}
void bottomsave() { //save bottom-left pos to EEPROM
    EEPROM.write(2,(blr*0.1));
    EEPROM.write(3,(bud*0.1));
}
void res1() { //set resolution to 64x48
    rows = 64;
    lines = 48;
}
void res2() { //set resolution to 48x36
    rows = 48;
    lines = 36;
}
void res3() { //set resolution to 32x24
    rows = 32;
    lines = 24;
}
void res4() { //set resolution to 16x12
    rows = 16;
    lines = 12;
}

void measure() {
    // Raw temperature values. This size must be less than lines.
    int rawValues[128];
    int yPos = bud;
    int yInc = ((mud - bud) * 2) / (lines - 1);
    int xPos = blr;
    int xInc = ((blr - mlr) * 2) / (rows - 1);
    int lastRawVal = readRawTemperature(TEMP_OBJECT);

    ud.writeMicroseconds(yPos);
    lr.writeMicroseconds(xPos);
    for (int x = 0; x < rows; x++) {
        // Pause for a moment for the temperature reading to settle down in the new position.
        lastRawVal = readRawTemperature(TEMP_OBJECT);
        for (int msWait = MIN_READ_WAIT; msWait > 0 && lastRawVal == readRawTemperature(TEMP_OBJECT); msWait--) {
            delay(1);
        }
        // Move a little away from the edge of when the reading is updated.
        delay(MIN_READ_WAIT / 5 + MIN_READ_WAIT);
        lastRawVal = readRawTemperature(TEMP_OBJECT);
        delay(MIN_READ_WAIT);
        for (int y = 0; y < lines; y++) {
            // Read and save sensor object temperature
            rawValues[y] = readRawTemperature(TEMP_OBJECT);
            if (abs(lastRawVal - rawValues[y]) > MAX_SAFE_TEMPERATURE_CHANGE) {
                // The temperature changed too much. Give the sensor time to warm up or cool down, and try again.
                delay(MIN_READ_WAIT);
                rawValues[y] = readRawTemperature(TEMP_OBJECT);
            }
            lastRawVal = rawValues[y];
            if (y != lines - 1) {
                yPos += yInc;
                ud.writeMicroseconds(yPos);
                // We need to wait long enough in this new position to read the new temperature.
                delay(MIN_READ_WAIT);
            }
        }
        if (x != rows - 1) {
            xPos -= xInc;
            lr.writeMicroseconds(xPos);
        }
        // Move fairly quickly so that we don't measure the latent temperature of objects in the middle.
        // Don't move too fast to cause a lot of jiggle.
        for (int i = 0; i < (lines - 1); i++) {
            yPos -= yInc;
            ud.writeMicroseconds(yPos);
            delay(2);
        }
        printValues(rawValues, lines);
    }
    finish();
}

/**
 * Read the MLX90614 sensor using the SMBus.
 * @param tempType Set to TEMP_AMBIENT or TEMP_OBJECT depending on the type of temperature you want to measure.
 * @return Returns the temperature in Kelvin x 50. To get actual Kelvin, divide by 50.
 */
int readRawTemperature(uint8_t tempType) {
    uint8_t values[3];
    static const uint8_t DEVICE = 0x5A<<1;

    smb_startWait(DEVICE+SMB_WRITE);
    smb_write(tempType);
    smb_start(DEVICE+SMB_READ);
    smb_read(values, sizeof(values));
    // TODO: Use the 3rd byte (PEC) to verify the checksum. When it's invalid, requery the value.

    // Return temperature value. The data is sent as little endian.
    return ((int *)values)[0];
}

long getAmbientTemp(){
    return (readRawTemperature(TEMP_AMBIENT) * 2 - TEMP_OFFSET) / 100;
}

void printValues(int *rawValues, int length){
    char st1[32];
    for (int idx = 0; idx < length; idx++) {
        count++;
        long tpl = (long)(rawValues[idx]) * 2 - TEMP_OFFSET;
        // Since Arduino does not support float printing, we emulate it.
        sprintf(st1, "%04li\t%s%li.%02li", count, (tpl < 0 ? "-" : ""), abs(tpl / 100), abs(tpl % 100));
        Serial.println(st1); //send the temperature
    }
}

void finish(){
    char roomtemp[8] = "";
    sprintf(roomtemp, "r%li", getAmbientTemp());
    Serial.println(roomtemp); //send the room temperature
    Serial.println("Stop");
    count = 0; // Reset the count.
    ud.writeMicroseconds(mud);
    lr.writeMicroseconds(mlr);
}



