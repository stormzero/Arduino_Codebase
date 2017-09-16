//Simulate(Mega75)
// Saved by Simulator for Arduino V0.97B
int m =0;
int d;
int f;
int E;
int g;
int h,i;
int D = 44;
int Eprom [253];
int Add;
int PIN = 13; //led Yellow dell'arduino
int buttonPin = 39;     // the number of the pushbutton pin
int interPin = 38; // il pin per l'interruttore della programmazione senza PC
int Dis [4][7]= //matrice display 7 seg. 0,1,2,3 - a,b,c,d,e,f,g
{
  {
    52,40,42,44,46,50,48      }
  ,{
    36,24,26,28,30,34,32      }
  ,
  {
    53,41,43,45,47,51,49      }
  ,{
    37,25,27,29,31,35,33      }
};
int led2Pinp=22;
int digit [10][7]= {
  {
    HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW //0  
  }
  ,{
    LOW,HIGH,HIGH,LOW,LOW,LOW,LOW  //1 
  }
  ,{
    HIGH,HIGH,LOW,HIGH,HIGH,LOW,HIGH  //2 
  }
  ,{
    HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH  //3
  }
  ,{
    LOW,HIGH,HIGH,LOW,LOW,HIGH,HIGH  // 4 
  }
  ,{
    HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH  // 5 
  }
  ,{
    LOW,LOW,HIGH,HIGH,HIGH,HIGH,HIGH  // 6  
  }
  ,{
    HIGH,HIGH,HIGH,LOW,LOW,LOW,LOW   // 7 
  }
  ,{
    HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH  // 8  
  }
  ,{
    HIGH,HIGH,HIGH,LOW,LOW,HIGH,HIGH   // 9 
  }         
};

void setup() {
  // Setup della porta seriale
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.flush();
  // initialize the LED DIGIT 1 pin as an output and set to LOW:
  pinMode (PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  for (int d =0; d<4; d++){
    for (int e=0; e<7; e++){
 	i = Dis [d][e];
      pinMode (i, OUTPUT);
      digitalWrite (i, LOW);
    }
  }
  pinMode(led2Pinp, OUTPUT);
  digitalWrite (led2Pinp,HIGH);
  pinMode(buttonPin, INPUT);
  pinMode (interPin, INPUT);
} 
void loop (){
  int v;
  for (v=0; v<4;v++)
  {
    int R;
    R=1;//scrivo rEAd sul display
    for (int d=0; d<7; d++){
      digitalWrite (Dis[0][d],digit [R][d]);    
    }
    R=2;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[1][d],digit [R][d]);    
    }
    R=3;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[2][d],digit [R][d]);    
    }
    R=4;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[3][d],digit [R][d]);    
    }
    delay (500);
    R=5;//scrivo PUsH sul display
    for (int d=0; d<7; d++){
      digitalWrite (Dis[0][d],digit [R][d]);    
    }
    R=6;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[1][d],digit [R][d]);    
    }
    R=7;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[2][d],digit [R][d]);    
    }
    R=8;
    for (int d=0; d<7; d++){
      digitalWrite (Dis[3][d],digit [R][d]) ;   
    }
    delay (500);
  }
}


