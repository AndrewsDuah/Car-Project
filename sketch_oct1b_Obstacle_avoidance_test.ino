#include<Servo.h>          

int leftSpeedPin =6;
int leftDir1 = 24;
int leftDir2 =25;
int motSpeed = 255;


int rightSpeedPin =5 ;
int rightDir1 = 22;
int rightDir2 = 23;


int turnMotSpeed = 50;
int stopSpeed = 0;

//sensor pins

int echoPin = 29;
int trigPin = 28;
float distance;
int duration;
int i;
float total;
float avgDistance;
int numMeas = 150;

// Servo
Servo myServo; 
int servoPin = 12;
int origPos = 90;
int leftPos = 180;
int rightPos = 0;
int thresholdDistance = 40;


void setup(){
pinMode(leftSpeedPin,OUTPUT);
pinMode(leftDir1, OUTPUT);
pinMode(leftDir2,OUTPUT);
pinMode(rightSpeedPin,OUTPUT);
pinMode(rightDir1, OUTPUT);
pinMode(rightDir2,OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin,OUTPUT);
myServo.attach(servoPin); 
myServo.write(origPos);

}

void loop(){
  distance = getDistance();

  if (distance <= thresholdDistance){
    moveStop();
    delay(500);
    moveBackward();
    delay(300);
    moveStop();
    delay(500);
    int distanceRight = lookRight();
    delay(300);
    int distanceLeft  = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = getDistance();
}

int  lookRight(){  
  myServo.write(rightPos);
  delay(500);
  int Rightdistance =  getDistance();
  delay(100);
  myServo.write(origPos);
  return Rightdistance;
}

int  lookLeft(){
  myServo.write(leftPos);
  delay(500);
  int Leftdistance = getDistance();
  delay(100);
  myServo.write(origPos);
  return Leftdistance;
  delay(100);
}

void moveStop(){
  
digitalWrite(rightDir1,LOW);
digitalWrite(rightDir2,LOW);
analogWrite(rightSpeedPin,stopSpeed);

digitalWrite(leftDir1,LOW);
digitalWrite(leftDir2,LOW);
analogWrite(leftSpeedPin,stopSpeed);
}

void moveForward(){

digitalWrite(rightDir1,HIGH);
digitalWrite(rightDir2,LOW);
analogWrite(rightSpeedPin,motSpeed);

digitalWrite(leftDir1,HIGH);
digitalWrite(leftDir2,LOW);
analogWrite(leftSpeedPin,motSpeed); 
  
}

void moveBackward(){

digitalWrite(rightDir1,LOW);
digitalWrite(rightDir2,HIGH);
analogWrite(rightSpeedPin,motSpeed);

digitalWrite(leftDir1,LOW);
digitalWrite(leftDir2,HIGH);
analogWrite(leftSpeedPin,motSpeed);
  
}

int turnRight(){
digitalWrite(leftDir1, HIGH);   
digitalWrite(leftDir2, LOW);    
analogWrite(leftSpeedPin, turnMotSpeed); 

digitalWrite(rightDir1, LOW);    
digitalWrite(rightDir2, HIGH);   
analogWrite(rightSpeedPin, turnMotSpeed);

delay(500); 

digitalWrite(leftDir1, HIGH); 
digitalWrite(leftDir2, LOW); 
analogWrite(leftSpeedPin, turnMotSpeed); 

digitalWrite(rightDir1, HIGH); 
digitalWrite(rightDir2, LOW);    
analogWrite(rightSpeedPin, turnMotSpeed); 
  
}

int turnLeft(){

digitalWrite(leftDir1, LOW);     
digitalWrite(leftDir2, HIGH);    
analogWrite(leftSpeedPin, turnMotSpeed);  

digitalWrite(rightDir1, HIGH);  
digitalWrite(rightDir2, LOW);    
analogWrite(rightSpeedPin, turnMotSpeed);

delay(500);  

digitalWrite(leftDir1, HIGH);    
digitalWrite(leftDir2, LOW);     
analogWrite(leftSpeedPin, turnMotSpeed);  

digitalWrite(rightDir1, HIGH);  
digitalWrite(rightDir2, LOW);    
analogWrite(rightSpeedPin, turnMotSpeed); 
}
int getDistance (){
total = 0;
for(i=1;i<=numMeas;i++){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);

  duration = pulseIn(echoPin,HIGH);

 int Distance = duration * 0.034/2;
  total += Distance;
  delay(15);
}
avgDistance = total/numMeas;
return avgDistance;
}