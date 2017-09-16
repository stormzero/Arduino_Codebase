// Simulate Uno
// Saved by Simulator for Arduino V0.96
// Saved by Simulator for Arduino V0.94E
// Arduino Shields cc2500 RF Shield demo code
// Saved by Simulator for Arduino V0.92
// www.arduino.com.au
// v1.00 21-Sept-2011 - first version
// tested on Arduino Mega

#include <SPI.h>   // inslude the SPI library:
#include "cc2500.h"   // inslude the SPI library:


const int CsPin = 8;      // piezo beeper pin
//const int SclkPin = 51;      // piezo beeper pin
//const int MosiPin = 52;      // piezo beeper pin
//const int MisoPin = 50;      // piezo beeper pin


const int SclkPin = 13;      // piezo beeper pin
const int MosiPin = 11;      // piezo beeper pin
const int MisoPin = 12;      // piezo beeper pin



byte serialin,reg,val,status1;
byte regs[64],rx[256],txbuffer[64];

unsigned long ms,old_ms; // note time needs to be unsigned longs
  
void setup()
{
  Serial.begin(9600);        // initialize the serial communication:
  Serial.print("Version 1.00");
  pinMode(CsPin, OUTPUT);   // initialize Beeper output
  digitalWrite(CsPin,1);
  pinMode(MosiPin, OUTPUT);   // initialize Beeper output
  pinMode(SclkPin, OUTPUT);   // initialize Beeper output
//  SPI.setClockDivider(SPI_CLOCK_DIV128);  
  SPI.begin();       // initialize SPI:
  initcc2500();  
//  command(SFSTXON); // turn on Freq Syn
  serialin = 'R';
}



void loop() 
{
byte i;

  ms = millis();

  if (Serial.available()) {   // check if data has been sent from the computer:
    serialin = Serial.read(); // copy serial data to LCD line 2
  }  
  
  if (serialin=='1') {
    sendByte(SRX);
    Serial.println("SRX ");    
  }
  
 if (serialin=='2') {
    sendByte(SIDLE);
    Serial.println("SIDLE");    
  }
  
 if (serialin=='3') {
    sendByte(SFSTXON);
    Serial.println("SFSTXON");    
  }
  
 if (serialin=='4') {
    sendByte(SXOFF);
    Serial.println("SXOFF");    
  }
  
  
  
  if (serialin=='X') {
    check_rx();
  }
  
  if (serialin=='T') {
    txmit();
  }
  
  
  if ((serialin=='R') || (serialin=='r')) {
      serialin = 0;
      Serial.println("");      
      Serial.print("     SS 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");

//      read_burst_regs();
      for (i=0; i<0x40; i++) {
        regs[i] = readreg(i);
        if ((i%16)==0) {
          Serial.println("");  
          outdata(i);
          Serial.write(':');
          Serial.write(' ');
          outdata(status1);        
        }
        outdata(regs[i]);

      }
      Serial.print(regs[0x3f]);                
      Serial.println("");                
  }
}


void  outdata(byte j)
{
  Serial.print((i>>4),HEX);     
  Serial.print((i&0x0f),HEX);     
  Serial.print(" ");     
}



byte readreg(byte address)
{
   digitalWrite(CsPin,0);
   delayMicroseconds(20);
 
   while (digitalRead(MisoPin)!=0) {
   }
   status1 = SPI.transfer(0xc0+address); 
   delayMicroseconds(10);    
   val = SPI.transfer(0);
   digitalWrite(CsPin,1);
   return(val);
}

const byte num[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};



void read_all_regs(void)
{
byte i;
      for (i=0; i<0x40; i++) {
        regs[i] = readreg(i);
      }
}


void read_burst_regs(void)
{
byte i;
    digitalWrite(CsPin,0);
   delayMicroseconds(200);
 
//   while (digitalRead(MisoPin)!=0) {
//   }
   status1 = SPI.transfer(0xc0); 
//   delayMicroseconds(1);    
   for (i=0; i<0x40; i++) {
     regs[i] = SPI.transfer(0);
   }
   digitalWrite(CsPin,1);
}




byte sendByte(byte data)
{
    digitalWrite(CsPin, LOW);     // enable device
//   delayMicroseconds(20);    
    while (digitalRead(MisoPin) == HIGH) {     // wait for device
    };
    status1 = SPI.transfer(data);   // send byte
    digitalWrite(CsPin, HIGH);    // disable device
    return(status1);    // return result
}

byte sendCommand(byte command, byte data)
{
    digitalWrite(CsPin, LOW);     // enable device
//   delayMicroseconds(500);    
    while (digitalRead(MisoPin) == HIGH) {     // wait for device
    };
    SPI.transfer(command);     // send command byte
    byte result = SPI.transfer(data);    // send data byte
    digitalWrite(CsPin, HIGH);    // disable device
    return(result);    // return result
}

byte sendStrobeCommand(byte command)
{
    return sendByte(command);     // send command
}

byte sendBurstCommand(byte command, byte* data,byte length)
{
    digitalWrite(CsPin, LOW);    // enable device
   delayMicroseconds(200);
    while (digitalRead(MisoPin) == HIGH) {     // wait for device
    };
    SPI.transfer(command);     // send command byte
    byte result = 0;

    for (int i=0; i<length; ++i) {    // send data bytes
        result = SPI.transfer(data[i]);
        data[i] = result;
    }
    digitalWrite(CsPin, HIGH);     // disable device
    return result;     // return result
}


void read_rx(void)
{
byte i;
    digitalWrite(CsPin,0);
   delayMicroseconds(10);
 
//   while (digitalRead(MisoPin)!=0) {
//   }
   status1 = SPI.transfer(0xff); 
   //delayMicroseconds(1);    
   for (i=0; i<0x10; i++) {
     rx[i] = SPI.transfer(0);
   }
   digitalWrite(CsPin,1);
}

void write_tx(byte x)
{
byte i;

   digitalWrite(CsPin,0);
   delayMicroseconds(10);
   status1 = SPI.transfer(0x7f); 
 
   for (i=0; i<x; i++) {
     status1 = SPI.transfer(txbuffer[i]);
   }
   digitalWrite(CsPin,1);
}

void  transmit(byte x)
{
  write_tx(x);
  sendByte(STX);
}


void   wait_rx(void)
{
  byte i;
    status1 = sendByte(SNOP);
  //  outdata(status1);
  
    if ((status1&0xf0)==0x70) {
      status1 = sendByte(SFTX);
      Serial.println("SFTX");      
    }
  
    if (((status1&0xf0)==0x10)||((status1&0xf0)==0x60)) {
      status1 = sendByte(SRX);
      read_rx();
      
      Serial.println("");  
      Serial.print("Received: ");        
//      newline();

      Serial.print(status1,HEX);
      for (i=0; i<0x10; i++) {
        Serial.print(rx[i],HEX);
      }
      for (i=0; i<0x10; i++) {
        Serial.write(rx[i]);
      }
      status1 = sendByte(SFRX);
          Serial.println("");  
    }
}


void  txmit(void)
{       
////
//  while ((sendByte(0x35)&0x1f)>1) { // not idle
//    Serial.print((sendByte(0x35)&0x1f),HEX);    
//    Serial.print(" ");    
//  };

    sendStrobeCommand(SFRX);  // Flush RX buffer
    sendStrobeCommand(SIDLE);  // Flush RX buffer


    Serial.println("Transmit");
 
    txbuffer[0] = 13;
    txbuffer[1] = 'H';
    txbuffer[2] = 'e';
    txbuffer[3] = 'l';
    txbuffer[4] = 'l';
    txbuffer[5] = 'o';
    txbuffer[6] = ' ';
    txbuffer[7] = ' ';
    txbuffer[8] = 'U';
    txbuffer[9] = 'n';
    txbuffer[10] = 'o';
    txbuffer[11] = ' ';
    txbuffer[12] = ' ';
    txbuffer[13] = '!';
 //   transmit(5);       


//    sendStrobeCommand(SIDLE);         // SIDLE: exit RX/TX
    sendBurstCommand(0x7F, txbuffer, 14);         // fill TX FIFO
    sendStrobeCommand(STX);         // STX: enable TX

//        sendStrobeCommand(CC2500_CMD_SIDLE);         // SIDLE: exit RX/TX
//        sendBurstCommand(0x7F, data, 5);         // fill TX FIFO
//        sendStrobeCommand(CC2500_CMD_STX);         // STX: enable TX
  delay(100);
    sendStrobeCommand(SFTX); 
}





void check_rx1(void)
{
  byte i,result,result1,length,pktLen,status[2];
  
    result = readreg(CC2500_REG_RXBYTES);     // read RX FIFO until empty
      
    do {
      result1 = result;
      result = readreg(CC2500_REG_RXBYTES);
    } while (result!=result1);

  if (result==0) {
    Serial.println("Ret0");     
    return;
  }


    
    pktLen = readreg(CC2500_REG_RXFIFO); // Read length byte
    Serial.println("H");
    Serial.println(pktLen,HEX);

    if (pktLen > 250)                  // If pktLen size <= rxBuffer
    {
      length = pktLen;                     // Return the large size

      sendStrobeCommand(SIDLE);     // set IDLE - MRFI code
      sendStrobeCommand(SFRX);      // Flush RXFIFO
      sendStrobeCommand(SRX);       // RX state - from MRFI
      Serial.println("Ret1"); 
                          // Error
    } else {
      sendBurstCommand(0xff, rx, pktLen); // Pull data
      length = pktLen;                     // Return the actual size
      sendBurstCommand(0xff, status, 2);
       
      for (i=0; i<pktLen; i++) {
        Serial.print(rx[i],HEX);
        Serial.print(" ");
      
      } 
                                            // Read appended status bytes
      Serial.println(status[1],HEX); // TI_CCxxx0_LQI_RX]&TI_CCxxx0_CRC_OK);
     Serial.println("Rx End"); 
    }          
}


void check_rx(void)
{
  byte i;
//    sendStrobeCommand(SIDLE);     // SIDLE: exit RX/TX
    byte result = sendCommand(0xfB, 0x00);     // read RX FIFO until empty

    Serial.print("Rx: ");    
    for (int i=0; i<result; ++i) {
        result = sendCommand(0xfF, 0x00);
        Serial.print(result);           
    }

    unsigned long startTime = millis();


    while ((millis() - startTime) < 5000) {       // try learning addresses for 5 seconds
        sendStrobeCommand(SRX);         // SRX: enable RX
        delay(10);         // wait a bit
        result = sendCommand(0xFB, 0x00);         // read RXBYTES register, result should be 0x11

        if (result >= 4) {
            Serial.print("Rx1: ");               
            result = sendCommand(0xBF, 0x00);            // single access RX FIFO to get number of bytes to read, should be 0x0E
            Serial.println(result,HEX);               
            if (result == 0x0d) {
                byte data[64];
                startTime = millis();                
                sendBurstCommand(0xFF, data, result);                 // read RX FIFO
                for (i=0; i<result; i++) {
//                  outdata(data[i]);
                  Serial.print(data[i]);                  
                }


                // read 2 remaining bytes
                result = sendCommand(0xBF, 0x00);
                outdata(result);                
                result = sendCommand(0xBF, 0x00);
                outdata(result);
                Serial.println("");
            } else {
                // something is not right, clear RX FIFO
                result = sendCommand(0xFB, 0x00);

                for (int i=0; i<result; ++i) {
                    sendCommand(0xBF, 0x00);
                }
            }
        }
        sendStrobeCommand(SIDLE);       // SIDLE: exit RX/TX
        delay(2);
    }

    sendStrobeCommand(SIDLE);     // SIDLE: exit RX/TX
    result = sendCommand(0xFB, 0x00);     // read RXBYTES register, should be 0
    for (int i=0; i<result; ++i) {
        sendCommand(0xBF, 0x00);
    }
    Serial.println("Rx End");                   
}

void resetcc2500()
{
  //  delayMicroseconds(5);  
    digitalWrite(CsPin, LOW);     // enable device
    delayMicroseconds(1);
    digitalWrite(CsPin, HIGH);     // disable device and wait at least 40 microseconds
    delayMicroseconds(41);
    digitalWrite(CsPin, LOW);     // enable device
    
//  Serial.print("Here rst");        
    while (digitalRead(MisoPin) == HIGH) {     // wait for device
    };
    SPI.transfer(SRES);     // send reset command (SRES)
    digitalWrite(CsPin, HIGH);     // disable device
}


void initcc2500()
{
//    init();     // initialize the CC2500
    resetcc2500();    // reset device (0x30)
    resetcc2500();    // reset device (0x30)
    

    // write configuration register: MCSM0 – Main Radio Control State Machine Configuration





//    sendCommand(CC2500_REG_IOCFG2, 0x0b);
//    sendCommand(CC2500_REG_IOCFG0, 0x06);
    sendCommand(CC2500_REG_PKTLEN, 0xff);
    sendCommand(CC2500_REG_PKTCTRL1, 0x04);
    sendCommand(CC2500_REG_PKTCTRL0, 0x05);
    sendCommand(CC2500_REG_ADDR, 0x00);
    sendCommand(CC2500_REG_CHANNR, 0x03);    
    sendCommand(CC2500_REG_FSCTRL1, 0x0a);
    sendCommand(CC2500_REG_FSCTRL0, 0x00);
    sendCommand(CC2500_REG_FREQ2, 0x5D);
    sendCommand(CC2500_REG_FREQ1, 0x44);
    sendCommand(CC2500_REG_FREQ0, 0xec);
    sendCommand(CC2500_REG_MDMCFG4, 0x2d);
    sendCommand(CC2500_REG_MDMCFG3, 0x3b);
    sendCommand(CC2500_REG_MDMCFG2, 0x73);
    sendCommand(CC2500_REG_MDMCFG1, 0x22);
    sendCommand(CC2500_REG_MDMCFG0, 0xF8);
    sendCommand(CC2500_REG_DEVIATN, 0x01);
    sendCommand(CC2500_REG_MCSM0, 0x07); 
    sendCommand(CC2500_REG_MCSM0, 0x18); // set auto cal
    sendCommand(CC2500_REG_FOCCFG, 0x1d);    
    sendCommand(CC2500_REG_BSCFG, 0x1c);
    sendCommand(CC2500_REG_AGCCTRL2, 0xc7);
    sendCommand(CC2500_REG_AGCCTRL1, 0x00);
    sendCommand(CC2500_REG_AGCCTRL0, 0xb2);
    sendCommand(CC2500_REG_FREND1, 0xb6);
    sendCommand(CC2500_REG_FREND0, 0x10);
    sendCommand(CC2500_REG_FSCAL3, 0xea);
    sendCommand(CC2500_REG_FSCAL2, 0x0A);
    sendCommand(CC2500_REG_FSCAL1, 0x00);
    sendCommand(CC2500_REG_FSCAL0, 0x11);    
    sendCommand(CC2500_REG_FSTEST, 0x59);    
    sendCommand(CC2500_REG_TEST2, 0x88);
    sendCommand(CC2500_REG_TEST1, 0x31);
    sendCommand(CC2500_REG_TEST0, 0x0B);
//    sendCommand(CC2500_REG_FIFOTHR, 0x07);
    sendCommand(CC2500_REG_PATABLE, 0xfe);

    // SIDLE: exit RX/TX
    sendStrobeCommand(CC2500_CMD_SIDLE);

    // SIDLE: exit RX/TX
//    sendStrobeCommand(CC2500_CMD_SIDLE);

    // SPWD: enter power down mode when CSn goes high
//    sendStrobeCommand(CC2500_CMD_SPWD);

    // SIDLE: exit RX/TX
//    sendStrobeCommand(CC2500_CMD_SIDLE);
    
}
