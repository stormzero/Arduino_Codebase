/*
// Saved by Simulator for Arduino V0.96.A.2
-- ******************  Traffic Signal Intersection  ************************
-- ******************  Created by Brett A. Langley  ************************
                                                                           *
-- This project simulates the sequence of lights necessary to control a    *
-- traffic intersection.  The Arduino Uno microprocessor with the Atmel    *
-- ATmega328 has only 1 complete port (PORTD) that is available for use.   *
-- Two extra address lines for the clear signal and enable (clk) are       *
-- required for control the data flow.  Four 74LS259 8-bit addressable     *
-- latches control light drivers.  This method extends the one complete    *
-- 8 bit port to 4 external 8 bit ports.  Schematics are provided.         *                                     *

-- Port definitions are as follows:

-- Port D Header Connections                                     
-- 10 Pin DIP    Port bit     Definition   Arduino Pin           
-- Pin 1         PB0          CLK          D8
-- Pin 2         PB1          CLR          D9
-- Pin 3         PB2          NC
-- Pin 4         PB3          NC
-- Pin 5         PB4          NC
-- Pin 6         PB5          NC
-- Pin 7         PB6          NC
-- Pin 8         PB7          NC
-- Pin 9                      GND
-- Pin 10                     VTG

-- Port C Header Connections
-- 10 Pin DIP    Port bit     Definition  Arduino Pin
-- Pin 1         PD0          A           D0
-- Pin 2         PD1          B           D1
-- Pin 3         PD2          C           D2
-- Pin 4         PD3          D           D3
-- Pin 5         PD4          Enorth      D4
-- Pin 6         PD5          Esouth      D5
-- Pin 7         PD6          Eeast       D6
-- Pin 8         PD7          Ewest       D7
-- Pin 9                      GND
-- Pin 10                     VTG

-- D - 1 = Light On; 0 = Light Off.
-- Enorth, Esouth, Eeast, Ewest - High active lines to select the 
--    correct 74LS259.
-- CLR - Low signal that resets all output pins on 74LS259.
-- CLK - Simulated signal to enable the 74LS259 once the data is
--    stable on Port D.
*/

/* Number of data values for light sequence. */
const byte LightDataLength = 32;
/* Indication when a long delay is required. */
const byte LgDy = 0xFF;
/* Indication when a short delay is required. */
const byte ShDy = 0x5F;
/* Time to make a long delay (10s). */
const int Long_Time = 10000;
/* Time to make a short delay (3s). */
const int Short_Time = 3000;

const byte LightData[LightDataLength] = {
    0xF8, 0x31, 0x3D, LgDy, 0x35, 0x3B, ShDy, 0x33, 
    0x39, 0x30, 0x3C, LgDy, 0x34, 0x3A, ShDy, 0x32, 
    0x38, 0xC1, 0xCD, LgDy, 0xC5, 0xCB, ShDy, 0xC3, 
    0xC9, 0xC0, 0xCC, LgDy, 0xC4, 0xCA, ShDy, 0xC2
};

/* Define the CLR on Pin D8 */
const byte CLRPin = 9;
/* Define the CLK on Pin D9 */
const byte CLKPin = 8;
/* Initial value for light sequence. */
const byte Initial_Seq = 0xF9;

void setup() 
{
  /* Set all bits of Port D to output. */
  DDRD = 0xFF;
  /* Makes bits 0 and 1 of Port B as outputs. */
  pinMode(CLRPin,OUTPUT);
  pinMode(CLKPin,OUTPUT);
  /* Make sure CLK pin is low before reset */
  digitalWrite(CLKPin,LOW);
  /* Clear all the latches. */
  digitalWrite(CLRPin,LOW);
  /* Delay to make sure that the latches clear. */
  delay(25);
  /* Set CLR pin low. */
  digitalWrite(CLRPin,HIGH);
  /* Delay to make sure output is stable. */
  delay(25);
  /* Set Port D to the initial light sequence. */
  PORTD = Initial_Seq;
  /* Send clock signal. */
  SEND_CLK();
}

void loop() 
{
  /* Set up the loop to sequence through the data. */
  for (int x=0; x < LightDataLength; x++)
    {
      switch (LightData[x])
        {
          /* Is the data for a long delay? */
          case LgDy:
//            {
              /* Wait 10 seconds. */
              delay(Long_Time);    
              break;
//            }
          /* Is the data for a short delay? */
          case ShDy:               
//            {
              /* Wait 3 seconds. */
              delay(Short_Time);   
              break;
//            }
          default:
//            {
              /* Set Port D to the next light sequence. */
              PORTD = LightData[x];
              /* Send clock signal. */
              SEND_CLK();
              break;
//            }
        };
    };              
}

void SEND_CLK()
{
  /* Set CLKPin to set the clock high. */
  digitalWrite(CLKPin,HIGH);
  /* Make a short delay so the clock is stable. */
  delay(25);
  /* Set CLKPin to set the clock low. */
  digitalWrite(CLKPin,LOW);
}
