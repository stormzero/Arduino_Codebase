// *-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-*
// |                                                                       |
// |                      -_-TriggerT by Travis9011 -_-                    |
// |                                                                       |
// |             ©2012 www.snapadventure.it - Alessandro Travi             |
// |                                                                       |
// *-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-*
 
#include <LiquidCrystal.h>  //Libreria per LCD
 
#define ENTER  11            //Pin a cui e' collegato il tasto Enter
#define ESC  10             //Pin a cui e' collegato il tasto Esc
#define BACKLIGHT  9
#define MENO  8            //Pin a cui e' collegato il tasto Meno
#define OPTION  1
#define PIU  0          //Pin a cui e' collegato il tasto Piu
 
boolean piu_set = LOW, meno_set = LOW, option_set = LOW;
unsigned int n_piu, n_meno;
byte i = 0;
int NScatti=300;
int NScattiSetting;
unsigned int principale = 0, principale1=0, principale2=0, principale3=0, principale4=0, mode=0;
boolean piu = LOW, meno = LOW, enter, esc, option;//Variabili associate ai quattro pulsanti nella modalita' scorrimento pagine
boolean piu0 = LOW, meno0 = LOW, enter0;
boolean set = LOW;//Entra nella modalita' settaggio
boolean set0 = LOW;
 
boolean setenter = LOW;//Entra nella modalita' settaggio
long tempo_btn = 0, debounce = 190;  //Tempo tra due letture successive di un bottone (300 ms)
 
unsigned long contaimpulsopiu =0;
unsigned long contaimpulsomeno =0;
 
unsigned long currentTime;
unsigned long loopTime;
 
/*=========== Variabili Macchina Fotografica =========================================================================================================*/
 
int shutter_on = 200;//tempo di pressione per attivare la cam, da settare intorno i 100 e 300
int lampo = 100;
long otturatore = 0; //posa B
long attesa = 0, attesas = 0, attesal = 0, attesaPIR = 0;
float shutter_off = 4000; // tempo di attesa intervallo
float shutter_off_setting=0;
long shutter_offL = 0;
long shutter_off_settingL=0;
 
int light =0;
int passaggio=0;
int wakeup = 300; //tempo per il fuoco
int wakewait = 200; //tempo risveglio / scatto
int outpin = 12; //uscita per lo scatto
 
int flash = 16;//uscita flash
int LDR = 5; //analogico
int SUONO = 4; //analogico
int EXT = 3; //analogico
int EXT_DIGIT = 17; //digitale
int letturaLDR = 0;
int letturaSuono = 0;
int letturaSuonoimp = 0;
int sensSuono = 100, sensSuonosetting = 3;
int sensLDR = 60, sensLDRsetting = 3;
int sensLDRLaser = 25, sensLDRLasersetting = 3;
int sogliaLDR = 0;
int sogliaSuono = 0;
int setsensorLuce = 0,setsensorSuono = 0,setsensorLaser = 0;
int setmod = 0, setmodL = 0, setmodPIR = 0;
 
/*SIMBOLI*/
 
byte symbolstop[8] = {
B00000,
B11111,
B11111,
B11111,
B11111,
B11111,
B00000,
};
byte symbolplay[8] = {
B00000,
B10000,
B11000,
B11100,
B11000,
B10000,
B00000,
};
 
byte symbolnormal[8] = {
B00000,
B01110,
B11111,
B11111,
B11111,
B01110,
B00000,
};
 
byte symbolmod[8] = {
B00000,
B00100,
B01110,
B11111,
B01110,
B00100,
B00000,
};
 
byte symbolsens[8] = {
B00000,
B01110,
B01110,
B01110,
B01110,
B01110,
B00000,
};
 
byte symbolsensno[8] = {
B00000,
B01110,
B01010,
B01010,
B01010,
B01110,
B00000,
};
 
//Display LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 
void setup()
{
  currentTime = millis();
  loopTime = currentTime;
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, HIGH);
  lcd.begin(8, 2);
 
  pinMode(ENTER, INPUT);
  pinMode(ESC, INPUT);
  pinMode(PIU, INPUT);
  pinMode(MENO, INPUT);
  pinMode(OPTION, INPUT);
  pinMode(SUONO,INPUT);
  pinMode(outpin, OUTPUT);
 
  pinMode(flash, OUTPUT);
 
  NScattiSetting=NScatti;
  lcd.createChar(1, symbolstop);
  lcd.createChar(2, symbolplay);
  lcd.createChar(3, symbolmod);
  lcd.createChar(4, symbolnormal);
  lcd.createChar(5, symbolsens);
  lcd.createChar(6, symbolsensno);
 
  lcd.setCursor(0,0);
  lcd.print("TriggerT");
  lcd.setCursor(0,1);
  lcd.print("  v1.5  ");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("   by   ");
   lcd.setCursor(0,1);
  lcd.print(" Travis ");
  delay(2000);
  lcd.clear();
 
}
 
void loop(){
 
  shutter_off_setting=shutter_off;
  backlight();
//LETTURA PULSANTI
if(set == LOW)
  {
    piu = digitalRead(PIU);
    meno = digitalRead(MENO);
    option = digitalRead(OPTION);
  }
  enter = digitalRead(ENTER);
  esc = digitalRead(ESC);
 
  //Se premo PIU incremento di uno il contatore pagine
  if(meno == HIGH && millis() - tempo_btn > debounce)
  {
 
    tempo_btn = millis();
    if(principale >= 0 && principale < 5){
    principale++;}
 
    if(principale1 >= 0 && principale1 < 5){
      principale1++;}
    if(principale2 >= 0 && principale2 < 6){
      principale2++;}
    if(principale3 >= 0 && principale3 < 6){
      principale3++;}
    if(principale4 >= 0 && principale4 < 4){
      principale4++;}
 
    if(principale == 4){
      principale = 0;}
    if(principale1 == 4){
      principale1 = 0;}
    if(principale2 == 5){
      principale2 = 0;}
    if(principale3 == 5){
      principale3 = 0;}
    if(principale4 == 3){
      principale4 = 0;}
  }
 
  //Se premo MENO decremento il contatore pagine
  if(piu == HIGH && millis() - tempo_btn > debounce)
  {
 
    tempo_btn = millis();
    if(principale > 0 && principale < 5){
    principale--;}
    if(principale1 > 0 && principale1 < 5){
      principale1--;
   }
   if(principale2 > 0 && principale2 < 6){
     principale2--;
   }
   if(principale3 > 0 && principale3 < 5){
     principale3--;
   }
   if(principale4 > 0 && principale4 < 4){
     principale4--;
   }
 }
 
  //Se premo ESC torno alla schermata Home uscendo anche da tutti i sottomenu
  if(esc == HIGH && millis() - tempo_btn > debounce)  //Quando premo "esc" torno alla schermata HOME
  {
 
    tempo_btn = millis();
    if(mode==0){
    principale = 0;}
 
    else if(mode==1){
    principale1 = 0;}
 
    else if(mode==2){
    principale2 = 0;}
 
    else if(mode==3){
    principale3 = 0;}
 
    else if(mode==4){
    principale4 = 0;}
 
    set = LOW;
  }
 
   if(option == HIGH && millis() - tempo_btn > debounce && mode >= 0 && mode < 5)  //Quando premo "esc" torno alla schermata HOME
  {
 
    principale=0;
    principale1=0;
    principale2=0;
    principale3=0;
    principale4=0;
    tempo_btn = millis();
     mode++;
     if(mode == 5)
      mode = 0;
 
  }
 
  /*----------------------------INTERVALLOMETRO-------------------------*/
  if(mode==0){
  switch (principale)
  {
  case 0:    //Schermata HOME
 
    // codice per pagina nr. 0 (HOME)
    lcd.setCursor(0,0);
    lcd.print("Timer         ");
    lcd.setCursor(0,1);
    lcd.print("Scatti               ");
 
if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      NScatti=NScattiSetting;
      tempo_btn = millis();
      set = !set;
    }
 
   if(set == HIGH)
    {
      digitalWrite(BACKLIGHT, LOW);
      if(NScatti!=0 && otturatore == 0){
 
        NScatti--; //decrementa numero scatti mancante
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Next:");
 
        lcd.setCursor(0,1);
        lcd.print("Fine:");
        lcd.print(NScatti);
 
        delay(wakewait); //Prepara per lo scatto
        scatto();
 
        shutter_off_setting=shutter_off_setting-1000;
        while (shutter_off_setting > 0){
          lcd.setCursor(5,0);
          shutter_off_settingL=shutter_off_setting;
          lcd.print(shutter_off_settingL/1000);
          lcd.print("\"");
          lcd.print("           ");
          shutter_off_setting = shutter_off_setting-500;
          delay(500);
 
        }
 
       }
 
       else if(NScatti!=0 && otturatore != 0){
 
        NScatti--; //decrementa numero scatti mancante
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Next:");
 
        lcd.setCursor(0,1);
        lcd.print("Fine:");
        lcd.print(NScatti);
 
        delay(wakewait); //Prepara per lo scatto
        lcd.setCursor(8,0);
        lcd.print("B");
        digitalWrite(outpin, HIGH); //Scatta
        delay(otturatore+500); //tempo otturatore aperto
        digitalWrite(outpin, LOW); //Stop scatto
 
        shutter_off_setting=shutter_off_setting-500;
        while (shutter_off_setting > 0){
          lcd.setCursor(5,0);
          shutter_off_settingL=shutter_off_setting;
          lcd.print(shutter_off_settingL/1000);
          lcd.print("\"");
          lcd.print("                      ");
          shutter_off_setting = shutter_off_setting-500;
          delay(500);
 
        }
 
       }
 
        else if(NScatti==0){
          digitalWrite(BACKLIGHT, HIGH);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Finito!     ");
          lcd.setCursor(0,1);
          lcd.print("A casa!      ");
          delay(4000);
 
          set = !set;
        }
    }
 
    break;
 
    case 1:
 
    lcd.setCursor(0,0);
    lcd.print("Set Int            ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
 
        shutter_off=shutter_off+1000;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( shutter_off > 0 )
          shutter_off=shutter_off-1000;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(shutter_off<60000){
    shutter_offL =shutter_off;
    lcd.print(shutter_offL/1000);
    lcd.print("\"");
 
                       }
 
    else conversioneminutif(shutter_off);
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 2:
 
    lcd.setCursor(0,0);
    lcd.print("N Scatti            ");
 
  if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
 
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
 
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
   if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        NScattiSetting++;
 
        contaimpulsopiu++;
 
        if (contaimpulsopiu>10) {
 
          NScattiSetting=NScattiSetting+10;
 
            }
 
        }
        else if(piu_set == LOW){ contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
 
        meno_set = !meno_set;
        if( NScattiSetting > 0 )
        {
          NScattiSetting--;
        contaimpulsomeno++;
 
        if (contaimpulsomeno>10) {
        NScattiSetting=NScattiSetting-10;
          if(NScattiSetting<0){NScattiSetting=0;}
                                  }
        }
 
      }
 
   else if(meno_set == LOW){ contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    lcd.print(NScattiSetting);
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
    break;
 
    case 3:   // Set Bulb
    lcd.setCursor(0,0);
    lcd.print("Bulb                      ");
 
  if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
 
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        otturatore=otturatore+1000;
        contaimpulsopiu++;
        if(contaimpulsopiu>15){
        otturatore=otturatore+10000;
        }
 
        }
        else if(piu_set == LOW){contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( otturatore > 0 )
          otturatore=otturatore-1000;
          contaimpulsomeno++;
        if(contaimpulsomeno>15){
        otturatore=otturatore-10000;
        }
      }
      else if(meno_set == LOW){contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1); 
 
    if(otturatore!=0 && otturatore<60000) {
     lcd.print(otturatore/1000);
     lcd.print("\"");
 
     }
 
     if(otturatore>=60000){
 
       conversioneminuti(otturatore);
 
                           }
 
    if(otturatore == 0) lcd.print("No");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
      break;
     }//switch
   }//if
 
   /*-------------------------------Trigger LUCE---------------------------*/
   if(mode==1){
  switch (principale1)
  {
  case 0:    //Schermata HOME
 
  option_set = digitalRead(OPTION);
  meno_set = digitalRead(MENO);
  piu_set = digitalRead(PIU);
 
    // codice per pagina nr. 0 (HOME)
    lcd.setCursor(0,0);
    lcd.print("Trigger     ");
 
if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
 
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      if(setsensorLuce==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(LDR);
      sogliaLDR=letturaLDR+sensLDR;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(LDR);
      if(letturaLDR > sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Luce!        ");
        delay(attesa);
        scatto();
 
        delay(800);
 
    }}
 
    }//if sensore Interno
 
    else if(setsensorLuce!=0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(EXT);
      sogliaLDR=letturaLDR+sensLDR;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(EXT);
      if(letturaLDR > sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Luce!        ");
        delay(attesa);
        scatto();
 
        delay(1000);
 
    }}
 
    }//if sensore ESTERNO
 
   }
    lcd.setCursor(0,1);
    if(set == LOW){
      passaggio=0;
      lcd.print("Luce   ");
 
    lcd.write(1);
    lcd.print("            ");}
    else{
      lcd.print("Luce   ");
 
    lcd.write(2);
    lcd.print("            ");}
 
    break;
 
    case 1:
 
    lcd.setCursor(0,0);
    lcd.print("Sensore         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setsensorLuce < 1)
        setsensorLuce++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setsensorLuce > 0 )
          setsensorLuce--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setsensorLuce==0){
    lcd.print("In");
    }
    else lcd.print("Ext");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 2:
 
    lcd.setCursor(0,0);
    lcd.print("Sensib.              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(sensLDRsetting < 5)
        sensLDRsetting++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( sensLDRsetting > 0 )
          sensLDRsetting--;
      }
    }
    lcd.setCursor(0,1);
    //lcd.print(sensLDRsetting);
 
    if(sensLDRsetting==0){sensLDR=350; lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
 
    else if(sensLDRsetting==1){sensLDR=225; lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensLDRsetting==2){sensLDR=100; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensLDRsetting==3){sensLDR=60; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6);}
    else if(sensLDRsetting==4){sensLDR=30;lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6);}
    else if(sensLDRsetting==5){sensLDR=15; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5);}
 
    if(set == LOW){
 
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
 
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 3:
 
    lcd.setCursor(0,0);
    lcd.print("Delay              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if (attesa<1000){
        attesa=attesa+10;
 
        contaimpulsopiu++;}
 
        if (contaimpulsopiu>10) {
 
          attesa=attesa+30;
          if (attesa>1000){attesa=1000;}
 
            }
 
        }
        else if(piu_set == LOW){ contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
 
        meno_set = !meno_set;
        if( attesa > 0 )
        {
          attesa=attesa-10;
        contaimpulsomeno++;
 
        if (contaimpulsomeno>10) {
        attesa=attesa-30;
          if(attesa<0){attesa=0;}
                                  }
        }
 
      }
 
   else if(meno_set == LOW){ contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
 
     if(attesa==1000){lcd.print(attesa/1000); lcd.print("\"   ");}
     else{lcd.print(attesa); lcd.print("ms   ");}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
     }//switch
   }//if
 
   /*-------------------------------Trigger SUONO-------------------------------*/
   if(mode==2){
  switch (principale2)
  {
  case 0:    //Schermata HOME
 
    option_set = digitalRead(OPTION);
    meno_set = digitalRead(MENO);
    piu_set = digitalRead(PIU);
    lcd.setCursor(0,0);
    lcd.print("Trigger     ");
 
if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
 
      tempo_btn = millis();
      set = !set;
    }
 
   if(set == HIGH)
    {
 
   /*----------------------Sensore INT e Modalità Reflex-----------------*/
      if(setsensorSuono==0 && setmod==1){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(SUONO);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(SUONO);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
        scatto();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
  /*----------------------Sensore EXT e Modalità Reflex-----------------*/
    else if(setsensorSuono==1 && setmod==1){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(EXT);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(EXT);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
        scatto();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
   /*----------------------Sensore INT e Modalità Flash-----------------*/
    else if(setsensorSuono==0 && setmod==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(SUONO);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(SUONO);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
         lampeggio();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
  /*----------------------Sensore EXT e Modalità Flash-----------------*/
    else if(setsensorSuono==1 && setmod==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(EXT);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(EXT);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
        lampeggio();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
  /*----------------------Sensore INT e Modalità Mista-----------------*/
    else if(setsensorSuono==0 && setmod==2){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(SUONO);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(SUONO);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
        misto();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
  /*----------------------Sensore EXT e Modalità Mista-----------------*/
    else if(setsensorSuono==1 && setmod==2){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaSuonoimp=analogRead(EXT);
      letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      sogliaSuono=letturaSuono+sensSuono;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaSuonoimp=analogRead(EXT);
        letturaSuono = constrain(abs(letturaSuonoimp - 512)-25,0,512);
      if(letturaSuono > sogliaSuono){
        lcd.setCursor(0,0);
        lcd.print("Soglia       ");
        lcd.setCursor(0,1);
        lcd.print("Suono!        ");
        delay(attesas);
        misto();
 
        delay(800);
 
        }}
 
    }// IF sensore e modalità
 
    }
 
        lcd.setCursor(0,1);
    if(set == LOW){
      passaggio=0;
      lcd.print("Suono  ");
 
    lcd.write(1);
    lcd.print("            ");}
    else{
      lcd.print("Suono  ");
 
    lcd.write(2);
    lcd.print("            ");}
 
    break;
 
    case 1:
 
    lcd.setCursor(0,0);
    lcd.print("Set Mod         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setmod < 2)
        setmod++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setmod > 0 )
          setmod--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setmod==0){lcd.print("Flash            ");}
    else if(setmod==1){ lcd.print("Reflex       ");}
    else lcd.print("Ref+Fl     ");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 2:
 
    lcd.setCursor(0,0);
    lcd.print("Sensore         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setsensorSuono < 1)
        setsensorSuono++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setsensorSuono > 0 )
          setsensorSuono--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setsensorSuono==0){
    lcd.print("In");
    }
    else lcd.print("Ext");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 3:
 
  lcd.setCursor(0,0);
    lcd.print("Sensib.              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(sensSuonosetting < 5)
        sensSuonosetting++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( sensSuonosetting > 0 )
          sensSuonosetting--;
      }
    }
    lcd.setCursor(0,1);
 
    if(sensSuonosetting==0){sensSuono=350; lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
 
    else if(sensSuonosetting==1){sensSuono=220; lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensSuonosetting==2){sensSuono=150; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensSuonosetting==3){sensSuono=100; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6);}
    else if(sensSuonosetting==4){sensSuono=50;  lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6);}
    else if(sensSuonosetting==5){sensSuono=15;  lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5);}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 4:
 
    lcd.setCursor(0,0);
    lcd.print("Delay              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if (attesas<1000){
        attesas=attesas+10;
 
        contaimpulsopiu++;}
 
        if (contaimpulsopiu>10) {
 
          attesas=attesas+30;
          if (attesas>1000){attesas=1000;}
 
            }
 
        }
        else if(piu_set == LOW){ contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
 
        meno_set = !meno_set;
        if( attesas > 0 )
        {
          attesas=attesas-10;
        contaimpulsomeno++;
 
        if (contaimpulsomeno>10) {
        attesas=attesas-30;
          if(attesas<0){attesas=0;}
                                  }
        }
 
      }
 
   else if(meno_set == LOW){ contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
 
     if(attesas==1000){lcd.print(attesas/1000); lcd.print("\"   ");}
     else{lcd.print(attesas); lcd.print("ms   ");}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
     }//switch
   }//if
 
   /*-------------------------------Trigger LASER----------------------------*/
    if(mode==3){
  switch (principale3)
  {
  case 0:    //Schermata HOME
 
  option_set = digitalRead(OPTION);
  meno_set = digitalRead(MENO);
  piu_set = digitalRead(PIU);
 
    // codice per pagina nr. 0 (HOME)
    lcd.setCursor(0,0);
    lcd.print("Trigger     ");
 
if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
 
      tempo_btn = millis();
      set = !set;
    }
 
   if(set == HIGH)
    {
      /*------Mod Laser Sensore interno e scatto flash---------*/
      if(setmodL==0 && setsensorLaser==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(LDR);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(LDR);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        lampeggio();
 
        delay(800);
 
    }}
      }
       /*------Mod Laser Sensore interno e scatto Reflex---------*/
      if(setmodL==1 && setsensorLaser==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(LDR);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(LDR);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        scatto();
 
        delay(800);
 
    }}
      }
 
      /*------Mod Laser Sensore esterno e scatto flash---------*/
      if(setmodL==0 && setsensorLaser==1){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(EXT);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(EXT);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        lampeggio();
 
        delay(800);
 
    }}
      }
       /*------Mod Laser Sensore esterno e scatto Reflex---------*/
      if(setmodL==1 && setsensorLaser==1){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(EXT);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(EXT);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        scatto();
 
        delay(800);
 
    }}
      }
 
       /*------Mod Laser Sensore interno e scatto Misto---------*/
      if(setmodL==1 && setsensorLaser==0){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(LDR);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(LDR);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        misto();
 
        delay(800);
 
    }}
      }
 
      /*------Mod Laser Sensore esterno e scatto Misto---------*/
      if(setmodL==1 && setsensorLaser==1){
     if(passaggio==0 || option_set == HIGH){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Calib...");
      letturaLDR=analogRead(EXT);
      sogliaLDR=letturaLDR-sensLDRLaser;
      delay(1500);
      passaggio++;
    }
 
      else if(passaggio =!0){
        letturaLDR=analogRead(EXT);
      if(letturaLDR < sogliaLDR){
        lcd.setCursor(0,0);
        lcd.print("Barriera       ");
        lcd.setCursor(0,1);
        lcd.print("Fermata!        ");
        delay(attesal);
        misto();
 
        delay(800);
 
    }}
      }
 
   }
    lcd.setCursor(0,1);
    if(set == LOW){
      passaggio=0;
      lcd.print("Laser  ");
 
    lcd.write(1);
    lcd.print("            ");}
    else{
      lcd.print("Laser  ");
 
    lcd.write(2);
    lcd.print("            ");}
 
    break;
 
    case 1:
 
    lcd.setCursor(0,0);
    lcd.print("Set Mod         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setmodL < 2)
        setmodL++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setmodL > 0 )
          setmodL--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setmodL==0){lcd.print("Flash            ");}
    else if(setmodL==1){lcd.print("Reflex       ");}
    else lcd.print("Ref+Fl");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
    case 2:
 
    lcd.setCursor(0,0);
    lcd.print("Sensore         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setsensorLaser < 1)
        setsensorLaser++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setsensorLaser > 0 )
          setsensorLaser--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setsensorLaser==0){
    lcd.print("In");
    }
    else lcd.print("Ext");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 3:
 
    lcd.setCursor(0,0);
    lcd.print("Sensib.              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(sensLDRLasersetting < 5)
        sensLDRLasersetting++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( sensLDRLasersetting > 0 )
         sensLDRLasersetting--;
      }
    }
    lcd.setCursor(0,1);
 
    if(sensLDRLasersetting==0){sensLDRLaser=25; lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
 
    else if(sensLDRLasersetting==1){sensLDRLaser=20; lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensLDRLasersetting==2){sensLDRLaser=15; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6); lcd.write(6);}
    else if(sensLDRLasersetting==3){sensLDRLaser=10; lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6); lcd.write(6);}
    else if(sensLDRLasersetting==4){sensLDRLaser=5;  lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(6);}
    else if(sensLDRLasersetting==5){sensLDRLaser=2;  lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5); lcd.write(5);}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 4:
 
    lcd.setCursor(0,0);
    lcd.print("Delay              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if (attesal<1000){
        attesal=attesal+10;
 
        contaimpulsopiu++;}
 
        if (contaimpulsopiu>10) {
 
          attesal=attesal+30;
          if (attesal>1000){attesal=1000;}
 
            }
 
        }
        else if(piu_set == LOW){ contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
 
        meno_set = !meno_set;
        if( attesal > 0 )
        {
          attesal=attesal-10;
        contaimpulsomeno++;
 
        if (contaimpulsomeno>10) {
        attesal=attesal-30;
          if(attesal<0){attesal=0;}
                                  }
        }
 
      }
 
   else if(meno_set == LOW){ contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
 
     if(attesal==1000){lcd.print(attesal/1000); lcd.print("\"   ");}
     else{lcd.print(attesal); lcd.print("ms   ");}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
     }//switch
   }//if
 
   /*-------------------------------Trigger Movimento----------------------------*/
    if(mode==4){
  switch (principale4)
  {
  case 0:    //Schermata HOME
 
  option_set = digitalRead(OPTION);
  meno_set = digitalRead(MENO);
  piu_set = digitalRead(PIU);
 
    // codice per pagina nr. 0 (HOME)
    lcd.setCursor(0,0);
    lcd.print("Trigger     ");
 
if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
 
      tempo_btn = millis();
      set = !set;
    }
 
   if(set == HIGH)
    {
      pinMode(EXT_DIGIT, INPUT);
      int valorePIR = digitalRead(EXT_DIGIT);
      /*------Mod Movimento scatto flash---------*/
      if(setmodPIR==1){
 
        if(valorePIR == HIGH){ //was motion detected
         lcd.setCursor(0,0);
        lcd.print("Mov.       ");
        lcd.setCursor(0,1);
        lcd.print("Rilevato        ");
        delay(attesaPIR);
        lampeggio();
 
        delay(3500);
  }
    }
 
       /*------Mod Movimento scatto Reflex---------*/
      if(setmodPIR==0){
 
        if(valorePIR == HIGH){ //was motion detected
         lcd.setCursor(0,0);
        lcd.print("Mov.       ");
        lcd.setCursor(0,1);
        lcd.print("Rilevato        ");
        delay(attesaPIR);
        scatto();
 
        delay(3500);
  }
      }
 
       /*------Mod Movimento scatto Misto---------*/
      if(setmodPIR==2){
 
        if(valorePIR == HIGH){ //was motion detected
         lcd.setCursor(0,0);
        lcd.print("Mov.       ");
        lcd.setCursor(0,1);
        lcd.print("Rilevato        ");
        delay(attesaPIR);
        misto();
 
        delay(3500);
  }
      }
 
   }
    lcd.setCursor(0,1);
    if(set == LOW){
      passaggio=0;
      lcd.print("PIR    ");
 
    lcd.write(1);
    lcd.print("            ");}
    else{
      lcd.print("PIR    ");
 
    lcd.write(2);
    lcd.print("            ");}
 
    break;
 
    case 1:
 
    lcd.setCursor(0,0);
    lcd.print("Set Mod         ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if(setmodPIR < 2)
        setmodPIR++;
      }
 
      if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
        meno_set = !meno_set;
        if( setmodPIR > 0 )
          setmodPIR--;
      }
    }
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
    if(setmodPIR==0){lcd.print("Reflex            ");}
    else if(setmodPIR==1){lcd.print("Flash       ");}
    else lcd.print("Ref+Fl");
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
  case 2:
 
    lcd.setCursor(0,0);
    lcd.print("Delay              ");
 
    if(enter == HIGH && millis() - tempo_btn > debounce)  //Premendo "enter" si entra nella sotto-modalita'
    {
      tempo_btn = millis();
      set = !set;
    }
 
    if(set == HIGH)
    {
      //Abilita l'ingresso in modalita' configurazione
      n_piu = 0;
      n_meno = 0;
      //Abilita i tasti "piu" e "meno" in modalita' incremento/decremento
      piu_set = digitalRead(PIU);
      meno_set = digitalRead(MENO);
 
      if(piu_set == HIGH && millis() - tempo_btn > debounce)  //Incremento "variabile" se premo tasto "piu"
      {
        tempo_btn = millis();
        n_piu++;
        piu_set = !piu_set;
        if (attesaPIR<1000){
        attesaPIR=attesaPIR+10;
 
        contaimpulsopiu++;}
 
        if (contaimpulsopiu>10) {
 
          attesaPIR=attesaPIR+30;
          if (attesaPIR>1000){attesaPIR=1000;}
 
            }
 
        }
        else if(piu_set == LOW){ contaimpulsopiu=0;}
 
       if(meno_set == HIGH && millis() - tempo_btn > debounce)  //Decremento "variabile" se premo tasto "meno"
      {
        tempo_btn = millis();
        n_meno++;
 
        meno_set = !meno_set;
        if( attesaPIR > 0 )
        {
          attesaPIR=attesaPIR-10;
        contaimpulsomeno++;
 
        if (contaimpulsomeno>10) {
        attesaPIR=attesaPIR-30;
          if(attesaPIR<0){attesaPIR=0;}
                                  }
        }
 
      }
 
   else if(meno_set == LOW){ contaimpulsomeno=0;}
    }
 
    lcd.setCursor(0,1);  //Scrivo il numero di scatti
 
     if(attesaPIR==1000){lcd.print(attesaPIR/1000); lcd.print("\"   ");}
     else{lcd.print(attesaPIR); lcd.print("ms   ");}
 
    if(set == LOW){
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(4);
      lcd.print("            ");}
    else{
      lcd.print("         ");
      lcd.setCursor(7,1);
      lcd.write(3);
      lcd.print("            ");}
 
  break;
 
     }//switch
   }//if
 
}//loop
 
  void conversioneminutif(float valorentrataf){
 
long minuti=0;
long secondi=0;
 
        secondi = valorentrataf/1000;
        minuti=secondi/60;
        secondi=secondi-(minuti*60);
         lcd.setCursor(0,1);
         lcd.print(minuti);
         lcd.print("'");
         lcd.print(secondi);
         lcd.print("\"");
}
 
void conversioneminuti(long valorentrata){
 
long minuti=0;
long secondi=0;
 
        secondi = valorentrata/1000;
        minuti=secondi/60;
        secondi=secondi-(minuti*60);
         lcd.setCursor(0,1);
         lcd.print(minuti);
         lcd.print("'");
         lcd.print(secondi);
         lcd.print("\"");
}
 
void backlight(){
 
  currentTime = millis();
  if(currentTime >= (loopTime + 10000)){
    digitalWrite(BACKLIGHT, LOW);   // toggles the LED on/off
    loopTime = millis();  // Updates loopTime
  }
 
  if(enter == HIGH || esc == HIGH || option == HIGH || piu == HIGH || meno == HIGH || option_set == HIGH || piu_set == HIGH || meno_set == HIGH){loopTime=millis(); digitalWrite(BACKLIGHT, HIGH);}
 
}
 
void scatto(){
        digitalWrite(outpin, HIGH); //Scatta
        delay(shutter_on); //Attendi fine scatto
        digitalWrite(outpin, LOW); //Stop scatto
             }
 
void lampeggio(){
        digitalWrite(flash, HIGH); //Scatta
        delay(lampo); //Attendi fine scatto
        digitalWrite(flash, LOW); //Stop scatto
            }
 
void misto(){
        digitalWrite(outpin, HIGH); //Scatta
        digitalWrite(flash, HIGH); //Scatta
        delay(shutter_on); //Attendi fine scatto
        digitalWrite(flash, LOW); //Stop scatto
        digitalWrite(outpin, LOW); //Stop scatto
}