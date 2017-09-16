// Simulate(Uno)
// Saved by Simulator for Arduino V0.97.A.5
// Saved by Simulator for Arduino V0.97A
// Saved by Simulator for Arduino V0.97A
// Convert string to hex

void setup() {
  // initialize serial:
  Serial.begin(9600);
NOP;
}

void loop() {
  int v = x2i("003C");
  Serial.println(v);
}


int x2i(char *s) 
{
int x = 0;
int i = 0;
  while (1>0) {
//  for(;;) {
    char c;
    c = s[i];
    if (c >= '0' && c <= '9') {
      x *= 16;
      x += c - '0'; 
    }
    else if (c >= 'A' && c <= 'F') {
      x *= 16;
      x += (c - 'A') + 10; 
    }
    else break;
//    s++;
    i++;
  }
  return x;
}
