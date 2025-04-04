/**
 * Joe
 * V1.1
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
 #define Lside 12
 #define LSensor 8
 #define Rside 2
 #define RSensor 4
 #define StartMod 10
 #define Rpos 13
 #define Rneg 11
 #define Lpos A5
 #define Lneg 6
 #define PWMRight 5
 #define PWMLeft 3
 #define switch1 A7
 #define switch2 A6
 #define lineLeft A0
 #define lineRight A1
 
// define objects               declares pointers to these objects
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotState* rstate;
StayOn* stayOn;
RobotAction* raction;
WorldState* wrldstate;
LINEsensor* linesensors[3];
IRsensor* irsensors[5];
 
 void updateMotors();
 
 void setup() {
     // define pinmodes
     pinMode(Rpos, OUTPUT);
     pinMode(Rneg, OUTPUT);
     pinMode(Lpos, OUTPUT);
     pinMode(Lneg, OUTPUT);
     pinMode(Lside, INPUT);
     pinMode(Lsensor, INPUT);
     pinMode(Rsensor, INPUT);
     pinMode(Rside, INPUT);
     pinMode(LeftLine, INPUT); 
     pinMode(RightLine, INPUT);
     pinMode(StartMod, INPUT);
     pinMode(switch1, INPUT);
     pinMode(switch2, INPUT);
 
     Serial.begin(9600);

    leftMotorDriver = new MotorDriver();            // dynamically allocates memory for the object and returns a pointer (assigns it to leftMotorDriver)
    rightMotorDriver = new MotorDriver();

    for (int i = 0; i < 3; i++) {
        linesensors[i] = new LINEsensor(0);     // the "0" in LINEsensor(0) indicates that the sensor value is initialized to 0.
      }
      for (int i = 0; i < 5; i++) {
        irsensors[i] = new IRsensor(0);         // the "0" in LINEsensor(0) indicates that the sensor value is initialized to 0.
      }
      raction = new RobotAction(leftMotorDriver, rightMotorDriver);   // dynamically allocates memory for the object and returns a pointer (assigns it to raction)
      wrldstate = new WorldState(linesensors, irsensors);
      stayOn = new StayOn(raction, wrldstate);
      rstate = new RobotState(wrldstate, stayOn, raction);

 }
 
 void loop() {
    pollsensors();
    updateMotors();
    rstate->win();
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
     analogWrite(L_PWM, leftSpeed);
     analogWrite(R_PWM, rightSpeed);
 }

 void pollsensors() {
    linesensors[0]->setValue(analogRead(LEFT_LINE));
    linesensors[1]->setValue(analogRead(RIGHT_LINE));
  
    irsensors[0]->setValue(digitalRead(LEFT_IR_90));
    irsensors[1]->setValue(digitalRead(LEFT_IR_45));
    irsensors[2]->setValue(digitalRead(RIGHT_IR_45));
    irsensors[3]->setValue(digitalRead(RIGHT_IR_90));
 }
