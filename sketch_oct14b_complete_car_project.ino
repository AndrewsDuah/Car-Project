#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Servo.h>

// Motor pins
int rightSpeedPin = 5;
int rightDir1 = 22;
int rightDir2 = 23;
int leftSpeedPin = 6;
int leftDir1 = 24;
int leftDir2 = 25;

// Motor speeds
int turnMotSpeed = 150;
int motSpeed = 255;
int stopSpeed = 0;

// Ultrasonic sensor pins
int echoPin = 29;
int trigPin = 28;
float distance;
long duration;
int i;
float total;
float avgDistance;
int numMeas = 10;
int thresholdDistance = 45; // Threshold distance in cm

// Servo
Servo myServo;
int servoPin = 12;
int origPos = 90;
int leftPos = 180;
int rightPos = 0;

// Buzzer pin (if used)
int buzzPin = 13;

// Mode flags
bool obstacleAvoidanceMode = false;
bool startPressedLast = false;   // Debounce variable for Start button
bool selectPressedLast = false;  // Debounce variable for Select button

void setup() {
  Serial.begin(9600);      // Serial Monitor baud rate
  Dabble.begin(9600);      // Dabble communication baud rate

  // Initialize motor control pins
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(rightDir1, OUTPUT);
  pinMode(rightDir2, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(leftDir1, OUTPUT);
  pinMode(leftDir2, OUTPUT);

  // Initialize buzzer pin (if used)
  pinMode(buzzPin, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  // Initialize servo
  myServo.attach(servoPin);
  myServo.write(origPos);

  Serial.println("Car Ready. Press Start to enter obstacle avoidance mode.");
}

void loop() {
  Dabble.processInput(); // Process input from Dabble app

  // Toggle Obstacle Avoidance Mode ON
  if (GamePad.isStartPressed()) {
    if (!startPressedLast) {  // Check for button press (debounce)
      obstacleAvoidanceMode = true;
      Serial.println("Obstacle Avoidance Mode ON");
      moveStop(); // Ensure the car stops before switching modes
    }
    startPressedLast = true;
  } else {
    startPressedLast = false;
  }

  // Toggle Obstacle Avoidance Mode OFF
  if (GamePad.isSelectPressed()) {
    if (!selectPressedLast) {  // Check for button press (debounce)
      obstacleAvoidanceMode = false;
      Serial.println("Obstacle Avoidance Mode OFF. Manual control active.");
      moveStop(); // Ensure the car stops before switching modes
    }
    selectPressedLast = true;
  } else {
    selectPressedLast = false;
  }

  // Execute code based on the current mode
  if (obstacleAvoidanceMode) {
    runObstacleAvoidance();
  } else {
    manualControl();
  }
}

// Function for manual control
void manualControl() {
  if (GamePad.isUpPressed()) {
    moveForward();
  } else if (GamePad.isDownPressed()) {
    moveBackward();
  } else if (GamePad.isLeftPressed()) {
    turnLeft();
  } else if (GamePad.isRightPressed()) {
    turnRight();
  } else if (GamePad.isSquarePressed()) {
    moveStop();
  } else {
    moveStop();
  }
}

// Function for obstacle avoidance
void runObstacleAvoidance() {
  distance = getDistance();
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

// Function to get distance from ultrasonic sensor
float getDistance() {
  total = 0;
  for (i = 0; i < numMeas; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms
    if (duration == 0) {
      duration = 30000; // Maximum distance if no echo
    }
    distance = duration * 0.034 / 2;
    total += distance;
    delay(15);
  }
  avgDistance = total / numMeas;
  return avgDistance;
}

// Function to look right with the servo
int lookRight() {
  myServo.write(rightPos);
  delay(500);
  int distance = getDistance();
  delay(100);
  myServo.write(origPos);
  delay(500);
  return distance;
}

// Function to look left with the servo
int lookLeft() {
  myServo.write(leftPos);
  delay(500);
  int distance = getDistance();
  delay(100);
  myServo.write(origPos);
  delay(500);
  return distance;
}

// Movement functions
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

  delay(400);  // Adjust the delay for turning duration
  moveStop();
}

void turnLeft() {
  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, HIGH);
  analogWrite(leftSpeedPin, turnMotSpeed);

  digitalWrite(rightDir1, HIGH);
  digitalWrite(rightDir2, LOW);
  analogWrite(rightSpeedPin, turnMotSpeed);

  delay(400);  // Adjust the delay for turning duration
  moveStop();
}

void moveStop() {
  digitalWrite(rightDir1, LOW);
  digitalWrite(rightDir2, LOW);
  analogWrite(rightSpeedPin, stopSpeed);

  digitalWrite(leftDir1, LOW);
  digitalWrite(leftDir2, LOW);
  analogWrite(leftSpeedPin, stopSpeed);
}
