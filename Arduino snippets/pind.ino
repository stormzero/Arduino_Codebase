
// Simulate(Uno)

byte b,c,d;

void setup() {
  // put your setup code here, to run once:
 DDRD = 0xf0;
 PORTD = 0x55;
 DDRB = 0xff;
 PORTB = 0xaa;
 DDRC = 0xff;
 PORTC = 0x5c;

 b = PINB;
 c = PINC;
 d = PIND;

 b = DDRB;
 c = DDRC;
 d = DDRD;

 b = PORTB;
 c = PORTC;
 d = PORTD;

 Serial.begin(9600);

}




void loop() {
  // put your main code here, to run repeatedly:

 Serial.print(PINB,HEX);
 Serial.print(' ');
 Serial.print(PINC,HEX);
 Serial.print(' ');
 Serial.print(PIND,HEX);
 Serial.println(' ');

}
