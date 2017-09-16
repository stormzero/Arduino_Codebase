// Simulate(Uno)
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A
// Saved by Simulator for Arduino V0.98A

float l1=10;
float l2=20;
float theta_j2,theta_j3,theta_j4;
int p=-44;

byte motor[4][4] = {
{1,2,3,4},
{1,2,3,4},
{1,2,3,4},
{1,2,3,4}
};

void joint_space(float p_foot, float q_foot)
{
  int alpha = 188;  
  float p = sqrt(sq(p_foot) + sq(q_foot));  
  float beta = atan(p_foot/q_foot) * 180*7/22;
  theta_j3 = acos((sq(l1) +sq(l2) -sq(p)) / (2*l1*l2)) * 7*180/22;    
  
  theta_j4 = 180 + asin(l2/p * sin(theta_j3*22/7/180)) * 180*7/22 - beta;  
                                               
  theta_j2 = 355 - (theta_j4-180) - theta_j3;
}

void joint_spacer(float p_foot, float q_foot)
{
  l1=112;
 l2=110;
  int alpha = 188;  //orientatio angle of ankle for robo standing at max heighti.e.,230mm hip-joint to ankle-joint
  float p = sqrt(sq(p_foot) + sq(q_foot));  // length of vector from hip C.S to ankle joint
  float beta = atan(p_foot/q_foot) * 180*7/22;// angle made by vector 'p' with vertical
  //theta_j3 = acos((sq(l1) +sq(l2) -sq(p)) / (2*l1*l2)) * 7*180/22;    //angle in degres

  theta_j3 = (sq(l1) +sq(l2) -sq(p))/(2*l1*l2) ;    
  theta_j3 = acos(theta_j3) * 7*180/22;   //angle in degres
  theta_j3 = acos((sq(l1) +sq(l2) -sq(p))/(2*l1*l2)) * 7*180/22;    
//  theta_j3 = theta_j3 * 7*180/22;   //angle in degres
  
  //theta_j4 = 180 + asin(l2/p * sin(theta_j3*22/7/180)) * 180*7/22 - beta;  //angle in degrees, 
  theta_j4 = sin(theta_j3*PI/180);
  theta_j4 = l2/p *theta_j4 ;                          //180 added to map it to 4 bar calculations
  theta_j4 = 180 + asin(theta_j4) * 180*7/22 - beta;
  theta_j2 = 355 - (theta_j4-180) - theta_j3;  //180 subtracted to get j4 in 1st qdrnt                                                
                                               //355 instead of 360 from fine tunning of ankle
}

void setup() {
  // put your setup code here, to run once:
 int j = 22*7/180;
// theta_j3 =acos((sq(112) +sq(110) -sq(203)) / (2*112*110))*(180/PI);
 theta_j3 =acos((sq(112) +sq(110) -sq(203))/ (2*112*110))*180/PI;
 float f1 = 180/PI;

  for(int i=0;i<4;i++){
    pinMode(motor[0][i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
 joint_spacer(1.2,2,4);
 joint_space(1.2,2,4);
}
