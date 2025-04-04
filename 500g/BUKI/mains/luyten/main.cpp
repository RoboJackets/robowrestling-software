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
 #include "states/moveForward.h"
 #include "states/stayOn.h"
 
 // pinouts
 const int LEFT_IR_90 = 12;
 const int LEFT_IR_45 = 8;
 const int RIGHT_IR_90 = 2;
 const int RIGHT_IR_45 = 4;
 const int MIDDLE_IR = 7;
 const int START_MODULE = 10;
 const int R_POS = 11;
 const int R_NEG = 13;
 const int L_POS = 6;
 const int L_NEG = A5;
 const int R_PWM = 5;
 const int L_PWM = 3;
 const int DIP_SWITCH_1 = A6;
 const int DIP_SWITCH_2 = A7;
 const int LEFT_LINE = A0;
 const int RIGHT_LINE = A1;
  
 // define objects
 MotorDriver *leftMotorDriver;
 MotorDriver *rightMotorDriver;
 
 // define functions
 void updateMotors();
 void stop();
 RobotAction* raction;
 MoveForward* rstate;
 StayOn* stayOn;
WorldState* wrldstate;
LINEsensor* linesensors [3];
IRsensor* irsensors [5];
 void setup() {
     // define pinmodes
     pinMode(R_POS, OUTPUT);
     pinMode(R_NEG, OUTPUT);
     pinMode(L_POS, OUTPUT);
     pinMode(L_NEG, OUTPUT);
     pinMode(LEFT_IR_90, INPUT);
     pinMode(LEFT_IR_45, INPUT);
     pinMode(MIDDLE_IR, INPUT);
     pinMode(RIGHT_IR_45, INPUT);
     pinMode(RIGHT_IR_90, INPUT);
     pinMode(LEFT_LINE, INPUT);
     pinMode(RIGHT_LINE, INPUT);
     pinMode(START_MODULE, INPUT);
     pinMode(DIP_SWITCH_1, INPUT);
     pinMode(DIP_SWITCH_2, INPUT);
 
     // instantiate objects
     leftMotorDriver = new MotorDriver();
     rightMotorDriver = new MotorDriver();
 
     Serial.begin(9600);
 
     raction = new RobotAction(leftMotorDriver, rightMotorDriver);
     rstate = new MoveForward(raction);
     wrldstate = new WorldState(linesensors, irsensors);
     stayOn = new StayOn(raction, wrldstate);
     
 }
 void pollsensors() {
  linesensors[0]->setValue(analogRead(A0));
  linesensors[1]->setValue(analogRead(A1));
}
 void loop() {
      //pollsensors()
     // updateState()
     updateMotors();

    rstate->runAlgorithm();

     // listen for stop signal
     if (!digitalRead(START_MODULE)) {
       while(true) {
         //brake
         stop();
       }
     }
     
 }
 
 void stop() {
   analogWrite(R_POS, 0);
   analogWrite(R_NEG, 0);
   analogWrite(L_POS, 0);
   analogWrite(L_NEG, 0);
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