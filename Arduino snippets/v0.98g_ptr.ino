const int  PIN_FIRE     =  2;
const int  LED_SMS_SEND = 13;

int  A_BUS_FIRE  = 0;
int  P_BUS_FIRE  = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_FIRE,INPUT);
  pinMode(LED_SMS_SEND,OUTPUT);

}

void loop()
{
  digitalWrite(LED_SMS_SEND,LOW);


  if(TestBus(&P_BUS_FIRE, &A_BUS_FIRE, PIN_FIRE)==HIGH)
  {
    digitalWrite(LED_SMS_SEND,HIGH);
    Serial.println("HIGH");
    delay(5000);
  }
  delay(1000);
}

int TestBus(int* P_BUS,int* A_BUS,int PIN)
{
 *A_BUS = digitalRead(PIN);
 if(*A_BUS!=*P_BUS)
 {
   *P_BUS=*A_BUS;
   return HIGH;
 }
 else
 {
   return LOW;
 }
}
