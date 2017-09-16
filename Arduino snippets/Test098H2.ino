const byte NumSens = 10;
boolean Tripped[NumSens][3]    = {false,true,false,    
                                  false,true,true,     
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,true,
                                  false,true,false}; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Testing");
  Serial.println(String(Tripped[9][2]));
}

void loop() {
  // put your main code here, to run repeatedly: 
  while(1); 
}
