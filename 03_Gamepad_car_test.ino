#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
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

  // put your setup code here, to run once:
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600); 
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
  myServo.write(origPos);     //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
  digitalWrite(rightDir1, HIGH);
  digitalWrite(rightDir2, LOW);
  analogWrite(rightSpeedPin, motSpeed);

  digitalWrite(leftDir1, HIGH);
  digitalWrite(leftDir2, LOW);
  analogWrite(leftSpeedPin, motSpeed); 
  }

  if (GamePad.isDownPressed())
  {
  digitalWrite(rightDir1, LOW);
  digitalWrite(rightDir2, HIGH);
  analogWrite(rightSpeedPin, motSpeed);

  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, HIGH);
  analogWrite(leftSpeedPin, motSpeed);
  }

  if (GamePad.isLeftPressed())
  {
  digitalWrite(leftDir1, LOW);     
  digitalWrite(leftDir2, HIGH);    
  analogWrite(leftSpeedPin, turnMotSpeed);  

  digitalWrite(rightDir1, HIGH);  
  digitalWrite(rightDir2, LOW);    
  analogWrite(rightSpeedPin, turnMotSpeed);
  }

  if (GamePad.isRightPressed())
  {
  digitalWrite(leftDir1, HIGH);   
  digitalWrite(leftDir2, LOW);    
  analogWrite(leftSpeedPin, turnMotSpeed); 

  digitalWrite(rightDir1, LOW);    
  digitalWrite(rightDir2, HIGH);   
  analogWrite(rightSpeedPin, turnMotSpeed);
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    myServo.write(180);
    delay(500);
    myServo.write(90);
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}
