    int LED = 1;
// Saved by Simulator for Arduino V0.98B

void setup()
{
    DDRJ = 255;        // Port.J komplett Ausgang
    PORTJ = 255;      // Port.J alle Ausgänge Ein
    delay(1000);
    PORTJ = 0;         // Port.J alle Ausgänge Aus
    delay(500);
}

void loop()
{
    if (LED > 128) {LED = 1}; // Prüfung ob höchstes Bit erreicht

    PORTJ = LED;        // Port.J wird neu gesetzt

    LED = LED << 1;         // Register von Port.J um 1 verschieben

    delay(500);
}
