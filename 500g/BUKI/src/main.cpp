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
#include "states/moveForward.h"

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
 
// define objects               allocates memory for these 5 objects
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
StayOn* rstate;
MoveForward* rstate2;
RobotAction* raction;
WorldState* wrldstate;
LINEsensor* linesensors [3];
IRsensor* irsensors [5];

// define functions
void updateMotors();
void stop();
void pollsensors();

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
  leftMotorDriver = new MotorDriver();            // creates instances of motor driver objects
  rightMotorDriver = new MotorDriver();

  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    linesensors[i] = new LINEsensor(0);
  }
  for (int i = 0; i < 5; i++) {
    irsensors[i] = new IRsensor(0);
  }
  raction = new RobotAction(leftMotorDriver, rightMotorDriver);   // creates instances of objects
  wrldstate = new WorldState(linesensors, NULL);
  rstate = new StayOn(raction, wrldstate);
  rstate2 = new MoveForward(raction);
}
void loop() {
    pollsensors();
    // updateState()
    updateMotors();
    // rstate->runAlgorithm();
    Serial.println(irsensors[2]->getValue());
    if (irsensors[2]->getValue()) {
      int stayoncounter = 200000;
      while (true) {
        pollsensors();
        updateMotors();

        if (irsensors[2]->getValue()) {
          raction->go();

        } else {
          rstate->runAlgorithm();
          stayoncounter--;
          if (stayoncounter <= 0){
            break;
          }
        }
      }
    } else {
      raction->spinLeft();
    }

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

  irsensors[0]->setValue(digitalRead(LEFT_IR_90));
  irsensors[1]->setValue(digitalRead(LEFT_IR_45));
  irsensors[2]->setValue(digitalRead(MIDDLE_IR));
  irsensors[3]->setValue(digitalRead(RIGHT_IR_45));
  irsensors[4]->setValue(digitalRead(RIGHT_IR_90));
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
  int leftDirection = leftMotorDriver->getDir();
  int leftSpeed = leftMotorDriver->getSpeed();

  if (leftDirection == 1) {  // if direction is forward
     digitalWrite(L_POS, 1);
     digitalWrite(L_NEG, 0);
  } else {                    // if direction is back
     digitalWrite(L_POS, 0);
     digitalWrite(L_NEG, 1);
  }

  int rightDirection = rightMotorDriver->getDir();
  int rightSpeed = rightMotorDriver->getSpeed();

  if (rightDirection == 1) {  // if direction is forward
     digitalWrite(R_POS, 0);
     digitalWrite(R_NEG, 1);
  } else {                    // if direction is back
     digitalWrite(R_POS, 1);
     digitalWrite(R_NEG, 0);
  }

  // controls the speed
  analogWrite(L_PWM, leftSpeed);
  analogWrite(R_PWM, rightSpeed);
}