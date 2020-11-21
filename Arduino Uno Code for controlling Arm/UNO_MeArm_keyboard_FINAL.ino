#include <Servo.h> 

Servo Base;
Servo Shoulder;
Servo Elbow;
Servo Claw;

int minPulse = 544;  
int maxPulse = 2400;
  
int  BaseAngle;
int  ShoulderAngle;
int  ElbowAngle;
int  ClawAngle;
char userCommand;

const int DigiPin41=12;
bool The_Thing;

void setup() {
  Serial.begin(9600);
  pinMode(DigiPin41, INPUT);
  Base.attach(11, minPulse, maxPulse);
  Base.write(90);  
  BaseAngle=90;
  
  Shoulder.attach(10, minPulse, maxPulse);
  Shoulder.write(90);
  ShoulderAngle=90;

  Elbow.attach(9, minPulse, maxPulse);
  Elbow.write(90);
  ElbowAngle=90;

  Claw.attach(5, minPulse, maxPulse);
  Claw.write(35);
  ClawAngle=35;
}
void loop() {
 The_Thing = digitalRead(DigiPin41); 
 if (Serial.available()>0 && The_Thing==HIGH){
  
    userCommand=Serial.read();  
                                  
    if (userCommand=='j' && BaseAngle<135){      
      BaseAngle+=1;
      Base.write(BaseAngle);         
}
    else if (userCommand=='l' && BaseAngle>50){ 
      BaseAngle-=1;
      Base.write(BaseAngle);
            
}                               
    else if (userCommand=='i' && ShoulderAngle<160){    
      ShoulderAngle+=1;
      Shoulder.write(ShoulderAngle);      
}
    else if (userCommand=='k' && ShoulderAngle>30){
      ShoulderAngle-=1;
      Shoulder.write(ShoulderAngle);      
}                                
    else if (userCommand=='s' && ElbowAngle<160){
      ElbowAngle+=1;
      Elbow.write(ElbowAngle);     
}
    else if (userCommand=='w' && ElbowAngle>20){
      ElbowAngle-=1;
      Elbow.write(ElbowAngle);       
}                                 
    else if (userCommand=='a' && ClawAngle<75){     
      ClawAngle+=1;
      Claw.write(ClawAngle);            
}
    else if (userCommand=='d' && ClawAngle>0){      
      ClawAngle-=1;
      Claw.write(ClawAngle);           
}
    else if (userCommand=='v'){      
      BaseAngle=90;
      Base.write(BaseAngle);
      delay(1000);
            
      ShoulderAngle=90;
      Shoulder.write(ShoulderAngle);
      delay(1000);
            
      ElbowAngle=90;
      Elbow.write(ElbowAngle);
      delay(1000);
            
      ClawAngle=35;
      Claw.write(ClawAngle);
      delay(1000);     
  }     
 } 
}
  
