    
// Saved by Simulator for Arduino V0.98.B.1
// Saved by Simulator for Arduino V0.98.B.1
// Saved by Simulator for Arduino V0.98.B.1
    int RCIN =1;                // Definition de la pin d'entrée du signal PPM du recepteur
    long  pulse_in = 0;        // Definition du pulse mesuré en ms
    int pulse_min= 1000;        // Definition du pulse min en ms
    int pulse_neutral =1500;    // Definition du pulse neutre en ms
    int pulse_max = 2000;      // Definition du pulse max en ms
    
    int led=0; //defintion de la pin de la led
    int led_on=50, led_off=50;// lon = temps d'allumage de la led, loff temps les eteinte.
    
    int config_sw =2; // defintion de la pin du sw de configuration
    int SW_1 = 3; // definition de la pin du sw 1
    int SW_2 = 4; // definition de la pin du sw 2
    int TRIG_SW_1 = 1300;// definition du trigger du sw 1
    int TRIG_SW_2 = 1700;// definition du trigger du sw 2
    
    
    void setup() 
    {
      pinMode (led, OUTPUT);  // 0 Accès à port à la clé avec LED
      pinMode(RCIN, INPUT);      // 1 ligne d'entrée du récepteur
      pinMode(config_sw, INPUT);      // 1 ligne d'entrée du sw de config
      pinMode (SW_1, OUTPUT);  // 
      pinMode (SW_2, OUTPUT);  // 
    }
    
    // Lit le signal PPM du récepteur ensuite, en fonction du temps du pulse fait divers choses..
    void loop () {
      pulse_in = pulseIn(RCIN, HIGH,20000);  
      //pulse_in= analogRead(A0);
      pulse_in= pulse_in*2;
      if (pulse_in < pulse_min || pulse_in >pulse_max){ // si le pulse est < a 1000ms ou > a 2000 
        digitalWrite(SW_1, LOW); // ferme SW_1
        digitalWrite(SW_2, LOW); // ferme SW_2
        flash(); // fait bliker la led !
      }
       else {
             
                  if (pulse_in <= TRIG_SW_1) digitalWrite(SW_1, HIGH); // allume SW_1
                  else if (pulse_in >= TRIG_SW_2) digitalWrite(SW_2, HIGH); // allume SW_1  
                  else{
                    digitalWrite(SW_1, LOW); // ferme SW_1
                    digitalWrite(SW_2, LOW); // ferme SW_2
                }
               
                    
          }
    }
    
    //Blink blink la led
    void flash(){
    for (int i=0; i <= 5; i++){
    digitalWrite(led, 1); delay (led_on); digitalWrite(led, 0); delay (led_off);  //led on; delay; led off ; delay.
    }
   }
