String sc = "ABC(DEF)";
 
void setup()
{
  Serial.begin(9600);
  ExtractData(sc);
}
 
void loop()
{
}
 
void ExtractData(String Text)
{
  int si = Text.indexOf('(');
  Serial.println(sc);
  Serial.println(si);
}