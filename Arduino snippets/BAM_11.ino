{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\tx400\tx800\tx1200\tx1600\tx2000\tx2400\tx2800\tx3200\tx3600\tx4000\tx4400\tx4800\tx5200\tx5600\tx6000\tx6400\tx6800\tx7200\tx7600\tx8000\f0\fs-24 volatile uint8_t g_timeslice[4] ; // one byte for each bit-position being displayed on a port.\par
// Saved by Simulator for Arduino V0.97.A.3\par
// Saved by Simulator for Arduino V0.97.A.3\par
// Saved by Simulator for Arduino V0.96.A.3\par
// Saved by Simulator for Arduino V0.96.A.2\par
// Saved by Simulator for Arduino V0.96.A.2\par
volatile uint8_t g_tick = 0;\par
volatile uint8_t g_bitpos = 0; // which bit position is currently being shown\par
uint8_t brightness[8]; // brightness for each LED on port D.\par
uint8_t slowtick = 0;\par
volatile uint8_t position = 0 ;\par
int brightness = 6\par
int intensity[4] = \{1,2,3,4\};\par
\par
#include <avr/io.h>\par
\par
void setup()\{\par
/*  pinMode(13, INPUT);\par
  digitalWrite(13, HIGH); //pullUP R\par
  pinMode(13, OUTPUT);  // pour tester ISR\par
*/\par
  led_init();\par
  led_encode_timeslices( brightness ) ;\par
\par
  // now a (simple) demonstration...\par
  // In the real-world, you'd probably want to decouple the\par
  // animation speed from the LED flicker-rate.\par
\}\par
\par
// simple initialisation of the port and timer\par
void led_init( void )\par
\{\par
  PORTD = 0x00 ; // All outputs to 0.\par
  DDRD = 0x7f ; // 4  outputs.\par
\par
  TCCR2A = _BV(WGM21) ; // set the timer to CTC mode.\par
  TCCR2B = _BV(CS20) | _BV(CS21) ; // use clock/32 tickrate\par
  g_bitpos = 0 ;\par
  OCR2A = 1 ; // initial delay.\par
  TIMSK2 = _BV(OCIE2A) ; // Enable the Compare Match interrupt\par
  sei();\par
\}\par
\par
// encode an array of 8 LED brightness bytes into the pattern\par
// to be shown on the port for each of the 8 timeslices.\par
void led_encode_timeslices( uint8_t intensity[] )\par
\{\par
  uint8_t portbits = 0;\par
  uint8_t bitvalue ;\par
\par
  for ( uint8_t bitpos = 0 ; bitpos < 4 ; bitpos++ )\par
  \{\par
    portbits = 0;\par
    bitvalue = 1 ;\par
    for ( byte ledpos = 0 ; ledpos < 4 ; ledpos++ )\par
    \{\par
      if (intensity[ ledpos ] & (1 << bitpos)) portbits |= bitvalue ;\par
      bitvalue = bitvalue << 1 ;\par
    \}\par
    g_timeslice[ bitpos ] = portbits ;\par
  \}\par
\}\par
\par
// Timer interrupt handler - called once per bit position.\par
ISR( TIMER2_COMPA_vect )\{\par
 /* static boolean state = false ;\par
  state = !state ;\par
  digitalWrite(13, state ?  HIGH : LOW);\par
  */\par
  g_bitpos ++ ;\par
  g_bitpos &= 7;\par
  PORTD = g_timeslice[ g_bitpos ] ;\par
  // now set the delay...\par
  TCNT2 = 0;\par
  OCR2A <<= 32 ;\par
  if (g_bitpos == 0) OCR2A = 32 ; // reset the compare match value.\par
  if (g_bitpos == 4) g_tick = 1 ; // give the main loop a kick.\par
\}\par
\par
void loop()\{\par
  while(g_tick==0)\{ /*wait for g_tick to be non-zero*/\par
  \}\par
  g_tick = 0 ; //consume the tick\par
  // make each of the LEDs slightly dimmer...\par
  for ( uint8_t index = 0 ; index < 8 ; index++ )\par
  \{\par
    if (brightness[ index ] > 0) brightness[ index ]-- ;\par
  \}\par
  // once every 30 ticks, advance the head of the sweep...\par
  slowtick-- ;\par
  if (slowtick==0)\par
  \{\par
    slowtick = 127;\par
    position++ ;\par
    position &= 7 ;\par
    brightness[ position ] = 255 ;\par
  \}\par
  // and now re-encode all the timeslices...\par
  led_encode_timeslices( brightness ) ;\par
\}\par
\par
\par
\par
\par
\par
\par
}
 