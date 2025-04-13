#include <Arduino.h>
// imports
#include "sensors/MotorDriver.h"
#include "states/robotState.h"
#include "action/robotAction.h"
#include "states/moveForward.h"
#include "states/stayOn.h"

#define Rpos A1
#define Rneg A0
#define Lpos A5
#define Lneg 8
#define PWMRight 13
#define PWMLeft 9
#define Lside A11
#define LSensor 7
#define Rside 0
#define RSensor 8
#define StartMod 29
#define testLED1 1
#define testLED2 2
#define testLED3 3
#define switch1 A7
#define switch2 A6
#define lineLeft A12
#define lineRight A10
void line();
void stop();
void turnLeft(double);
void turnRight(double);
void back(double);
void forward(double);
void rotateRight(double);
void rotateLeft(double);
void lineLeftt();
void lineRightt();
void updateMotors();

MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;

RobotAction *raction;
StayOn* stayOn;
WorldState* wrldstate;
LINEsensor* linesensors [3];
IRsensor* irsensors [5];

void setup() {
  pinMode(Rpos, OUTPUT);
  pinMode(Rneg, OUTPUT);
  pinMode(Lpos, OUTPUT);
  pinMode(Lneg, OUTPUT);
  pinMode(StartMod, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(lineLeft, INPUT);
  pinMode(lineRight, INPUT);
  Serial.begin(9600);

  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();

  for (int i = 0; i < 3; i++) {
    linesensors[i] = new LINEsensor(0);
  }

  raction = new RobotAction(leftMotorDriver, rightMotorDriver);
  wrldstate = new WorldState(linesensors, irsensors);
  stayOn = new StayOn(raction, wrldstate);
}

void pollsensors() {
  linesensors[0]->setValue(analogRead(lineLeft));
  linesensors[1]->setValue(analogRead(lineRight));
}
void loop() {
  stayOn->runAlgorithm();
  updateMotors();
  pollsensors();
  Serial.print(linesensors[0]->getValue());
  Serial.print("  ");
  Serial.println(linesensors[1]->getValue());

}
void lineRightt() {
  back(140);
  delay(220);
  rotateRight(130);
  delay(150);
  forward(0);
}
void lineLeftt() {
  back(140);
  delay(220);
  rotateLeft(130);
  delay(150);
  forward(0);
}
void stop() {
  analogWrite(PWMRight, 0);
  analogWrite(PWMLeft, 0);
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}
// void forward(double speed) {
//   analogWrite(13, speed);
//   analogWrite(A9, speed);
//   analogWrite(A1, 250);
//   analogWrite(A0, 0);
//   analogWrite(A5, 250);
//   analogWrite(A8, 0);
// }
void back(double speed) {
  analogWrite(PWMRight, speed);
  analogWrite(PWMLeft, speed);
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 250);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 250);
}
void rotateRight(double speed) {
  analogWrite(PWMRight, speed);
  analogWrite(PWMLeft, speed);
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 250);
  analogWrite(Lpos, 250);
  analogWrite(Lneg, 0);
}
void rotateLeft(double speed) {
  analogWrite(PWMRight, speed);
  analogWrite(PWMLeft, speed);
  analogWrite(Rpos, 250);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 250);
}
void turnRight(double speed) {
  analogWrite(PWMRight, speed);
  analogWrite(PWMLeft, speed);
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 250);
  analogWrite(Lneg, 0);
}
void turnLeft(double speed) {
    analogWrite(PWMRight, speed);
  analogWrite(PWMLeft, speed);
  analogWrite(Rpos, 250);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}

void updateMotors() {
  int leftDirection = leftMotorDriver->getDir();
  int leftSpeed = leftMotorDriver->getSpeed();

  if (leftDirection == 1) {  // if direction is forward
    analogWrite(Lpos, 250);
    analogWrite(Lneg, 0);
  } else {                    // if direction is back
    analogWrite(Lpos, 0);
    analogWrite(Lneg, 250);
  }

  int rightDirection = rightMotorDriver->getDir();
  int rightSpeed = rightMotorDriver->getSpeed();

  if (rightDirection == 1) {  // if direction is forward
    analogWrite(Rpos, 250);
    analogWrite(Rneg, 0);
  } else {                    // if direction is back
    analogWrite(Rpos, 0);
    analogWrite(Rneg, 250);
  }

// controls the speed

   analogWrite(PWMLeft, leftSpeed);
   analogWrite(PWMRight, rightSpeed);
}