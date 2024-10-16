#include <Servo.h>

int ServoPin = 7;
int servoOrig = 90;
int leftPos = 180;
int rightPos = 0;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
pinMode(ServoPin,OUTPUT);
myServo.attach(ServoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
myServo.write(servoOrig);
delay(500);
}
