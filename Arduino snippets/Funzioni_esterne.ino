

// Dichiarazione della funzione che attiva radio 1
int radio_attiva_1()
{
  
  digitalWrite(LED1, HIGH);  //accende il led
        digitalWrite(LCDLight, HIGH);  //accende luce LCD
        lcd.setCursor(0, 0);
        lcd.print("ON AIR radio 1  ");
        lcd.setCursor(0, 1);
        lcd.print("RX 144--> TX 430");
        delay(lungh_coda);               // autoritenuta di DUE SECONDI
        digitalWrite(LED1, LOW);   //spegne il led
        radio=0;
  return (radio);
}

// Dichiarazione della funzione che attiva radio 2
int radio_attiva_2()
{ 
  
  digitalWrite(LED2, HIGH);  //accende il led
        digitalWrite(LCDLight, HIGH);  //accende luce LCD
        lcd.setCursor(0,0);
        lcd.print("ON AIR radio 2  ");
        lcd.setCursor(0, 1);
        lcd.print("RX 430--> TX 144");
        delay(lungh_coda);               // autoritenuta di DUE SECONDI
        digitalWrite(LED2, LOW);   //spegne il led
        radio=0;
  return (radio);
}
