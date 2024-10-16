#include <Servo.h>          

int leftSpeedPin = 6;
int leftDir1 = 24;
int leftDir2 = 25;

int rightSpeedPin = 5;
int rightDir1 = 22;
int rightDir2 = 23;

int turnMotSpeed = 150;
int motSpeed = 255;
int stopSpeed = 0;

// Ultrasonic sensor pins
int echoPin = 29;
int trigPin = 28;
float distance;
int duration;
int i;
float total;
float avgDistance;
int numMeas = 10;
int thresholdDistance = 45;  // Increased the threshold distance to 45 cm

// Servo
Servo myServo; 
int servoPin = 12;
int origPos = 90;
int leftPos = 180;
int rightPos = 0;

void setup() {
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(leftDir1, OUTPUT);
  pinMode(leftDir2, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(rightDir1, OUTPUT);
  pinMode(rightDir2, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(servoPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(origPos);

  Serial.begin(9600);  // Begin serial communication to monitor distance readings
}

void loop() {
  distance = getDistance();
  Serial.println(distance);  // Print the distance readings to the Serial Monitor

  if (distance <= thresholdDistance) {
    moveStop();
    delay(300);  
    moveBackward();
    delay(300);  
    moveStop();
    delay(300);
    
    int distanceRight = lookRight();
    delay(200);  
    int distanceLeft = lookLeft();
    delay(200);

    if (distanceRight >= distanceLeft) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward(); 
  }
}

int lookRight() {  
  myServo.write(rightPos);  
  delay(200);  // Reduced to match servo speed
  int distance = getDistance();
  delay(100);
  myServo.write(origPos);
  return distance;
}

int lookLeft() {
  myServo.write(leftPos);  
  delay(200);  
  int distance = getDistance();
  delay(100);
  myServo.write(origPos);
  return distance;
}

void moveStop() {
  digitalWrite(rightDir1, LOW);
  digitalWrite(rightDir2, LOW);
  analogWrite(rightSpeedPin, stopSpeed);

  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, LOW);
  analogWrite(leftSpeedPin, stopSpeed);
}

void moveForward() {
  digitalWrite(rightDir1, HIGH);
  digitalWrite(rightDir2, LOW);
  analogWrite(rightSpeedPin, motSpeed);

  digitalWrite(leftDir1, HIGH);
  digitalWrite(leftDir2, LOW);
  analogWrite(leftSpeedPin, motSpeed); 
}

void moveBackward() {
  digitalWrite(rightDir1, LOW);
  digitalWrite(rightDir2, HIGH);
  analogWrite(rightSpeedPin, motSpeed);

  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, HIGH);
  analogWrite(leftSpeedPin, motSpeed);
}

void turnRight() {
  digitalWrite(leftDir1, HIGH);   
  digitalWrite(leftDir2, LOW);    
  analogWrite(leftSpeedPin, turnMotSpeed); 

  digitalWrite(rightDir1, LOW);    
  digitalWrite(rightDir2, HIGH);   
  analogWrite(rightSpeedPin, turnMotSpeed);

  delay(300);  // Adjusted turning delay for faster turning
}

void turnLeft() {
  digitalWrite(leftDir1, LOW);     
  digitalWrite(leftDir2, HIGH);    
  analogWrite(leftSpeedPin, turnMotSpeed);  

  digitalWrite(rightDir1, HIGH);  
  digitalWrite(rightDir2, LOW);    
  analogWrite(rightSpeedPin, turnMotSpeed);

  delay(300);  // Adjusted turning delay for faster turning
}

float getDistance() {  
  total = 0;
  for(i = 1; i <= numMeas; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  
    total += distance;
    delay(10);  // Reduced delay between ultrasonic measurements
  }
  avgDistance = total / numMeas;
  return avgDistance;
}
