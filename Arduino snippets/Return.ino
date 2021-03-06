{\rtf1\ansi\ansicpg1252\deff0\deflang3081{\fonttbl{\f0\fnil\fcharset0 Courier New;}}
\viewkind4\uc1\pard\f0\fs-24 #include <EEPROM.h> // utilisation de EEPROM\par
const int len_eeprom = 16;\par
int eeprom_addr = 0;\par
int eeprom_crc = 0;\par
byte eeprom_value = 0;\par
byte eeprom_cks = 0;\par
int eeprom_get_cks()\{\par
for (int eeprom_address = 0; eeprom_address < len_eeprom-1; eeprom_address++)\{\par
eeprom_value = EEPROM.read(eeprom_address);\par
eeprom_crc = eeprom_crc + eeprom_value;\par
eeprom_crc = eeprom_crc & 0xFF;\par
\}\par
return eeprom_crc;\par
\}\par
boolean eeprom_check_cks()\{\par
eeprom_cks = eeprom_get_cks();\par
Serial.println(eeprom_cks);\par
eeprom_value = EEPROM.read(len_eeprom-1);\par
Serial.println(eeprom_value);\par
if(eeprom_cks == eeprom_value)\par
\{ \par
return true;\par
\}\par
else \par
\{\par
return false;\par
\}\par
\}\par
void setup() \{\par
// Debugging output\par
Serial.begin(9600);\par
boolean ret = 0;\par
ret = eeprom_check_cks();\par
Serial.println(ret);\par
\par
if(ret == true)\{ \par
Serial.println("cks ok");\par
\}else\{ \par
Serial.println("Erreur CKS");\par
\}\par
\}\par
void loop() \{\par
\}\par
}
 