// Saved by Simulator for Arduino V0.98.C.3 refer to vitronics.com.au
// Saved by Simulator for Arduino V0.98C refer to arduino.com.au
// Saved by Simulator for Arduino V0.98.C.1 refer to vitronics.com.au
  int instellen=LOW;
  int eenuur=999;
  int eenminuut=999;
  int onevenseconde=LOW;
  int evenseconde=HIGH;
  int backuphour;
  int backupminute;
  int tempminute;
  int temphour;
int minute=12;
int hour=2;
float timer_a;
String s;

 void setup(){
  pinMode(6,INPUT);      // gelijk zetten vanaf 00:00
  pinMode(7, OUTPUT);     //output naar de ledje   
  pinMode(8, OUTPUT);     //output naar de schakeldraad relais 
 }
void loop(){
 timer_a = 1234.2;
  s = "Test if cleared on reset?";
   if (digitalRead(6) == HIGH )//test of schakelaar voor 2 minuten verder 0,4 seconde word ingedrukt.
   {
   delay (200);
   }
   if (digitalRead(6) == HIGH )
   { 
    delay (200);
   }
   if (digitalRead(6) == HIGH )
 {
  temphour=hour; //plaats de waarde van het uur van de klok in de tijdelijke temphour
  tempminute=minute; // plaats de waarde van de minuut van de klok in de tijdelijke tempminute 
  backuphour=0;
  backupminute=0;
  digitalWrite(7,HIGH);
  delay (1000);
  digitalWrite(7,LOW);
  delay (1000); 
}
  if ((temphour >= 1) && (instellen==LOW)) 
{
 eenuur=0;       //rest aanvangswaarde op nul
 } 
if (temphour >= 12) 
{
 (temphour=temphour-12); 
 }
if (eenuur<=31) //test of hij 60 minuten gelopen heeft.
 {
  digitalWrite(7,onevenseconde);//schakelt led aan.
  digitalWrite(8,onevenseconde);//schakelt relais aan. 
  delay (1935);
  digitalWrite(7,evenseconde);//schakelt led aan.
  digitalWrite(8,evenseconde);//schakelt relais aan.
  delay (1936);
  eenuur++ ;
  instellen=HIGH;
 }
 
 if (eenuur==31) //test hij met 1 uur loup klaar is.
 {
  instellen=LOW; //zorg ervoor dat het programma om klok te laten lopen weer werkt 
  temphour-- ;
 }}

