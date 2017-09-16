
// Saved by Simulator for Arduino V0.96.A.3
// Saved by Simulator for Arduino V0.95A
// Saved by Simulator for Arduino V0.95A
struct robot_data
{
  int left_motor_speed;
  int right_motor_speed;
  int light_sensor;
  int left_bumper_switch;
  int right_bumper_switch;
};

void TurnLeft   ( struct robot_data *robot_pstruct);
void TurnRight  ( struct robot_data *robot_pstruct);
void GoStraight ( struct robot_data *robot_pstruct);
void PrintReport( int i, struct robot_data *robot_pstruct);




void setup(void)
{
  struct robot_data MyRobot_struct = {1, 2, 4, 7, 34};  //Declaration
  int i;                                   //Declaration
  struct robot_data *MyRobot_pstruct = 0;                         // initionlizing pointer to null
  
  
  
  MyRobot_pstruct= &MyRobot_struct; //asssign address of Kens ROBOT Stuctor 
  
  Serial.begin(9600);
  cls(); // clear the serial monitor screen
  
  // SERIAL PRINT ADD INDEX LIGHT ECT..  



    randomSeed(analogRead(0));

  for(i=0; i<=10; i++)
  {
    GetLightData(MyRobot_pstruct);
    if(MyRobot_pstruct->light_sensor >=60)
      TurnRight(MyRobot_pstruct);
    else if (MyRobot_pstruct->light_sensor >=40)
      GoStraight(MyRobot_pstruct);
    else
      TurnLeft(MyRobot_pstruct); 
      
    PrintReport(i,MyRobot_pstruct);
    
    delay(200);      //delay between comands
    
  }
  
  Serial.print("\nFinished\n");
 
}
 
void GetLightData( struct robot_data *robot_pstruct)              //
{
  long randomNum_li = 0;          
  int MIN = 0;                          
  int MAX = 100;
  
 
  randomNum_li = random (MIN,MAX);
  
  robot_pstruct->light_sensor = randomNum_li;

}  

void TurnRight( struct robot_data *robot_pstruct)              //
{ 
  robot_pstruct->left_motor_speed = 25;
  robot_pstruct->right_motor_speed = 0;
}  

void GoStraight( struct robot_data *robot_pstruct)              //
{
  robot_pstruct->left_motor_speed = 50;
  robot_pstruct->right_motor_speed = 50;
 
}

void TurnLeft( struct robot_data *robot_pstruct)              //
{
  robot_pstruct->left_motor_speed = 0;
  robot_pstruct->right_motor_speed = 25;
}

void PrintReport(int i, struct robot_data *robot_pstruct)              // Everything inside ()is Paremiters list
{ 
    Serial.print(i);
    Serial.print("\t");
    Serial.print( robot_pstruct->light_sensor );
    Serial.print("\t\t");
    Serial.print( robot_pstruct->left_motor_speed);
    Serial.print("\t\t\t");
    Serial.print(robot_pstruct->right_motor_speed);
    Serial.print("\t\t\t");
    
    if ( robot_pstruct->left_motor_speed == 25 && robot_pstruct->right_motor_speed == 0)
      Serial.print( "Turn Right\n");
    else if ( robot_pstruct->left_motor_speed == 0 && robot_pstruct->right_motor_speed == 25)
      Serial.print( "Turn Left\n");
    else 
      Serial.print( "Go Straight\n");
}

// *************************************************
//
// clear the screen function
// this function sends the escape character to the terminal
// to clear the screen
//
// *************************************************
void cls(void )
{                            // begin block for cls function
    byte FF=27;                  // the character to clear the terminal screen
    Serial.write(FF);  // send the character to the screen
    delay(1000);               // delay while the screen gets cleared
}                            // end block for cls function


void loop()
{
}

