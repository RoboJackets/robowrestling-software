/**
 * Joe
 * File that outlines Shorti's main
 * 1/30/2025
 */

#include <Arduino.h>

// imports
#include "sensors/MotorDriver.h"
#include "states/robotState.h"
#include "action/robotAction.h"
#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"
#include "states/stayOn.h"

// pinouts
const int L_POS = 2;
const int L_NEG = 1;
const int R_POS = 3;
const int R_NEG = 4;
const int L_PWM = 5;
const int R_PWM = 6;
const int LEFT_LINE = 23;
const int RIGHT_LINE = 22;
const int LEFT_IR_90 = 21;
const int LEFT_IR_45 = 20;
const int MIDDLE_IR = 19;
const int RIGHT_IR_45 = 18;
const int RIGHT_IR_90 = 17;
const int START_MODULE = 16;
 
// define objects
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;

// define functions
void updateMotors();
void stop();
void pollsensors();


StayOn* rstate;
RobotAction* raction;
WorldState* wrldstate;
LINEsensor* linesensors [3];

void setup() {
  // pinmode definitions
  pinMode(L_POS, OUTPUT);
  pinMode(L_NEG, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_POS, OUTPUT);
  pinMode(R_NEG, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(LEFT_LINE, INPUT);
  pinMode(RIGHT_LINE, INPUT);
  pinMode(LEFT_IR_90, INPUT);
  pinMode(LEFT_IR_45, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR_45, INPUT);
  pinMode(RIGHT_IR_90, INPUT);
  pinMode(START_MODULE, INPUT);
  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();

  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    linesensors[i] = new LINEsensor(0);
  }
  raction = new RobotAction(leftMotorDriver, rightMotorDriver);
  wrldstate = new WorldState(linesensors, NULL);
  rstate = new StayOn(raction, wrldstate);
}
void loop() {
    pollsensors();
    // updateState()
    updateMotors();
    raction->go();
    //rstate->runAlgorithm();
    // Serial.print(leftMotorDriver->getSpeed());
    // Serial.print(" ");
    // Serial.println(rightMotorDriver->getSpeed());
    // listen for stop signal
    // if (!digitalRead(START_MODULE)) {
    //   while(true) {
    //     //brake
    //     stop();
    //   }
    // }
    
}
void stop() {
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}

void pollsensors() {
  linesensors[0]->setValue(analogRead(LEFT_LINE));
  linesensors[1]->setValue(analogRead(RIGHT_LINE));
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
  int leftDirection = leftMotorDriver->getDir();
  int leftSpeed = leftMotorDriver->getSpeed();

  if (leftDirection == 1) {  // if direction is forward
     analogWrite(L_POS, 1);
     analogWrite(L_NEG, 0);
  } else {                    // if direction is back
     analogWrite(L_POS, 0);
     analogWrite(L_NEG, 1);
  }

  int rightDirection = rightMotorDriver->getDir();
  int rightSpeed = rightMotorDriver->getSpeed();

  if (rightDirection == 1) {  // if direction is forward
     analogWrite(R_POS, 1);
     analogWrite(R_NEG, 0);
  } else {                    // if direction is back
     analogWrite(R_POS, 0);
     analogWrite(R_NEG, 1);
  }

  // controls the speed
  Serial.print(leftSpeed);
  Serial.print(" ");
  Serial.println(rightSpeed);
  analogWrite(L_PWM, leftSpeed);
  analogWrite(R_PWM, rightSpeed);
}