   
int termatikopano1 = 2;    //TERMATIKO PANW THESIS
int termatikokato1 = 3;    // TERMATIKO KATW THESIS
int palmoi1 = 4;           // EISODOS PSIFIAKI PALMWN KINHTIRA 1 
int thlexirismopano1 = 5;  //EISODOS THLEXIRISMOY GIA PANW
int thlexirismokato1 = 6;  //EISODOS THLEXIRISMOY GIA KATW

int sun1 = 0;             //ANALOGIKH EISODOS AISTHTIRIOY HLIOY
int potensiometro1 = 1;   //ANALOGIKH EISODOS POTESIOMETROY GIA SET POINT HLIOY
int potensiometro2 = 2;   //ANALOGIKH EISODOS POTESIOMETROY GIA arithmo strofwn
int diavasexrono = 3;

int pano1 = 8;       //PSIFIAKI EKSODOS GIA KINHSH PANW KINHTIRA 1
int kato1 = 9;       //PSIFIAKI EKSODOS GIA KINHSH KATW KINHTIRA 1

int hlios1 = 0;      //METABLITH GIA THN TIMH TOY HLIOY
int setpoint1 =0;     //METABLITH GIA TO SET POINT APO POTENSIOMETRO
int counter1 = 0;     //METABLITH GIA THN METRISH TWN PALMWN TOY KINHTIRA
int pcounter1 = 0;    //METABLITH GIA THN PROIGOYMENI KATASTASH TVN PALMWN KINHTIRA
int shmaia1 = 0;      //METABLITH GIA THN PROIGOYMENI KATASTASH TVN PALMWN KINHTIRA
int shmaia2 = 0;     //METABLITH GIA THN PROIGOYMENI KATASTASH TVN PALMWN KINHTIRA

int isterisi = 0;  //METABLITH GIA RHN TIMH TIS YSTERISHS
int strofes1 = 0;   //METABLHTH ME MEGISTO ARITHMO STROFWN
int strofes2 = 0;
int pth1 = LOW;       //METABLHTH PANW THESIS 
int kth1 = LOW;       //METABLHTH KATW THESIS
int tkato1 = LOW;
int tpano1 = LOW;
unsigned long xronosk =0;
unsigned long xronosp =0;
int time1 = 0;
unsigned long  time2 = 0;
int pforakk = 1;
int pforakp = 1;
//int xronosp = 0;
//int xronosk = 0;

void setup()
{
Serial.begin(9600); 
pinMode (termatikopano1,INPUT);     //TERMATIKO PANW THESIS EISODOS
pinMode (termatikokato1,INPUT);     //TERMATIKO KATW THESIS EISODOS
pinMode (palmoi1,INPUT);           // EISODOS PALMWN KINHTIRA 1 
pinMode (thlexirismopano1,INPUT);  //EISODOS THLEXIRISMOY GIA PANW
pinMode (thlexirismokato1,INPUT);  //EISODOS THLEXIRISMOY GIA KATW
pinMode(pano1, OUTPUT);
pinMode(kato1, OUTPUT);
digitalWrite (pano1,LOW);    //MHDENISMOS METABLHTHS GIA THN KATASTASH TOY RELE PANW
digitalWrite (kato1,LOW);    //MHDENISMOS METABLHTHS GIA THN KATASTASH TOY RELE KATW 
counter1 = 0;                //ARXIKOPOIHSH METRITH
pcounter1 = 0;               //ARXIKOPOIHSH METRITH
}

void loop() 
  {

    hlios1 = analogRead(sun1);      // DIAVASE THN ENTASH TOY HLIOY
    setpoint1 = analogRead(potensiometro1);      // DIAVASE TO SET POINT
    pth1 = digitalRead(termatikopano1);
    kth1 = digitalRead(termatikokato1);
    tpano1 = digitalRead (thlexirismopano1);
    tkato1 = digitalRead (thlexirismokato1);
    pcounter1 = digitalRead(palmoi1);        // DIABADE TOYS PALMOYS
    strofes2 = analogRead(potensiometro2); 
    strofes1 = map(strofes2, 0, 1023, 0, 150);
    time1  = analogRead(diavasexrono);
    time2 = map(time1, 0, 1023, 0, 1800000);
     
    
    Serial.println(hlios1);
    Serial.println(setpoint1);
    //Serial.println(strofes1);
    //Serial.println(pth1);
    //Serial.println(kth1);
    //Serial.println(tpano1);
    //Serial.println(counter1);   
    //Serial.println(xronosk);
    //Serial.println(xronosp);
    //Serial.println(pforakk);
    //Serial.println(pforakp);
    //Serial.println(millis());
    //Serial.println(time2);
    //delay (1000);
    
   
    if (pth1 == HIGH)
    {
      digitalWrite (kato1,LOW) ;              //KANE TO RELE PANW LOW
      digitalWrite (pano1,LOW); 
      counter1 = 0;
      
    }
    if (kth1 == HIGH )
    {
        digitalWrite (kato1,LOW) ;              //KANE TO RELE PANW LOW
        digitalWrite (pano1,LOW); 
        counter1 = strofes1;
       
    }
 
  if ( tkato1 == LOW && tpano1 == LOW)
  {
    
          
      if ((hlios1 >= setpoint1 + isterisi) && (counter1 < strofes1))     //AN O HLIOS EINAI PANW APO TO SET POINT KAI O COUNTER EINAI MIKROTERO APO TO MEGISTO TVN STROFWN KAI DEN EINAI ENEGOPIHMENOS O THLEXIRISMOS GIA PANO KAI GIA KATW
      {
      
           if (pforakk == 1)
           {
           xronosk = millis ();
           pforakk = 0;
           }
           if (xronosk + time2 < millis())
           {
             
              if (pcounter1 == LOW)                   //AN H KATASTASH TWN PALMVN EINAI LOW KANE TH SHMAIA 0
                {
                  shmaia1 = 0; 
                }
              if (pcounter1 == HIGH && shmaia1 == 0)    //AN H KATASTASH TWN PALMWN EINAI HIGH KAI H SHMAIA EINAI 0
                {
                  counter1 = counter1 + 1;
                  shmaia1 = 1;
                }
              pforakp = 1;
              digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
              digitalWrite(kato1, HIGH);             //KANE TO RELE PANW HIGH
              if (counter1 == strofes1)
              {
                 digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
                 digitalWrite(kato1,LOW);               //KANE TO RELE PANW LOW
      
              }
        }
      }
 
  if ((hlios1  <= setpoint1 - isterisi) && (counter1 > 0) )           //AN O HLIOS EINAI KATW APO TO SET POINT KAI O COUNTER DEN EINAI 0 KAI DEN EINAI ENEGOPIHMENOS O THLEXIRISMOS GIA PANO KAI GIA KATW
      {
         if (pforakp == 1)
           {
           xronosp = millis();
           pforakp = 0;
           }
           if (xronosp + time2 < millis())
           {
              if (pcounter1 == LOW)                   //AN H KATASTASH TWN PALMVN EINAI LOW KANE TH SHMAIA 0
                {
                  shmaia2 = 0;
                }
              if (pcounter1 == HIGH && shmaia2 == 0)    //AN H KATASTASH TWN PALMWN EINAI HIGH KAI H SHMAIA EINAI 0
                {
                  counter1 = counter1 - 1;
                  shmaia2 = 1;
                } 
               pforakk =1;
              digitalWrite (kato1,LOW) ;              //KANE TO RELE PANW LOW
              digitalWrite (pano1,HIGH);             //KANE TO RELE KATW HIGH
              if (counter1 == 0 )
              {
                 digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
                 digitalWrite(kato1,LOW);               //KANE TO RELE PANW LOW 
              }
         } 
      }
  }
    
   if (tkato1 == HIGH && tpano1 == LOW && counter1 < strofes1)
  {
     if (pcounter1 == LOW)                   //AN H KATASTASH TWN PALMVN EINAI LOW KANE TH SHMAIA 0
     {
        shmaia1 = 0;
         
      }
      if (pcounter1 == HIGH && shmaia1 == 0)    //AN H KATASTASH TWN PALMWN EINAI HIGH KAI H SHMAIA EINAI 0
      {  
          counter1 = counter1 + 1;
          shmaia1 = 1;
         
       }
       digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
       digitalWrite(kato1, HIGH);             //KANE TO RELE PANW HIGH
       if (counter1 == strofes1)
         {
             digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
             digitalWrite(kato1,LOW);               //KANE TO RELE PANW LOW
      
          }
       
  
  }
 
   if ( tkato1 == LOW && tpano1 == HIGH && counter1 > 0)
  {
     if (pcounter1 == LOW)                   //AN H KATASTASH TWN PALMVN EINAI LOW KANE TH SHMAIA 0
     {
        shmaia1 = 0;
         
      }
      if (pcounter1 == HIGH && shmaia1 == 0)    //AN H KATASTASH TWN PALMWN EINAI HIGH KAI H SHMAIA EINAI 0
      {  
          counter1 = counter1 - 1;
          shmaia1 = 1;
         
       }
          digitalWrite(pano1,HIGH) ;              //KANE TO RELE KATW LOW
          digitalWrite(kato1, LOW);             //KANE TO RELE PANW HIGH
          if (counter1 == 0 )
          {
              digitalWrite(pano1,LOW) ;              //KANE TO RELE KATW LOW
              digitalWrite(kato1,LOW);               //KANE TO RELE PANW LOW 
           }
       
      }
  }

