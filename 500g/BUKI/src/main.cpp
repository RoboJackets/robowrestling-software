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
 #define Lside 12
 #define Lsensor 8
 #define Rside 2
 #define Rsensor 4
 #define MSensor 7
 #define StartMod 10
 #define Rpos 6
 #define Rneg 11
 #define Lpos 3
 #define Lneg 5
 #define switch1 A6
 #define switch2 A7
  
 // define objects
 MotorDriver *leftMotorDriver;
 MotorDriver *rightMotorDriver;
 
 // define functions
 void updateMotors();
 void stop();
 RobotAction* raction;
 StayOn* rstate;
 StayOn* stayOn;
  WorldState* wrldstate;
  LINEsensor* linesensors [3];
  IRsensor* irsensors [5];
 void setup() {
     // define pinmodes
     pinMode(Rpos, OUTPUT);
     pinMode(Rneg, OUTPUT);
     pinMode(Lpos, OUTPUT);
     pinMode(Lneg, OUTPUT);
     pinMode(StartMod, INPUT);
     pinMode(switch1, INPUT);
     pinMode(switch2, INPUT);
 
     // instantiate objects
     leftMotorDriver = new MotorDriver();
     rightMotorDriver = new MotorDriver();
 
     Serial.begin(9600);
 
     for (int i = 0; i < 3; i++) {
        linesensors[i] = new LINEsensor(0);
      }
      for (int i = 0; i < 5; i++) {
        irsensors[i] = new IRsensor(0);         // the "0" in LINEsensor(0) indicates that the sensor value is initialized to 0.
      }
      raction = new RobotAction(leftMotorDriver, rightMotorDriver);   // dynamically allocates memory for the object and returns a pointer (assigns it to raction)
      wrldstate = new WorldState(linesensors, irsensors);
      stayOn = new StayOn(raction, wrldstate);
      rstate = new RobotState(wrldstate, stayOn, raction);
     // wait for start signal
     while (!digitalRead(StartMod)) {
       Serial.print(digitalRead(StartMod));
       Serial.println(" Waiting for start signal");
     }
 }
 void pollsensors() {
  linesensors[0]->setValue(analogRead(A0));
  linesensors[1]->setValue(analogRead(A1));
}
 void loop() {
      pollsensors();
     // updateState()
     updateMotors();
     if (digitalRead(MSensor)) {
       rstate->runAlgorithm();
     } else {
       stop();
     }
     // listen for stop signal
     if (!digitalRead(StartMod)) {
       while(true) {
         //brake
         stop();
       }
     }
     
 }
 
 void stop() {
   analogWrite(Rpos, 0);
   analogWrite(Rneg, 0);
   analogWrite(Lpos, 0);
   analogWrite(Lneg, 0);
 }
 
 /**
  * Implemented for Shorti's motordrivers to conform to the
  * simple motordriver with speed and direction.  
  */ 
 void updateMotors() {
     int leftDirection = leftMotorDriver->getDir();
     int leftSpeed = leftMotorDriver->getSpeed();
 
     if (leftDirection == 1) {  // if direction is forward
         analogWrite(Lpos, leftSpeed);
         analogWrite(Lneg, 0);
     } else {                    // if direction is back
         analogWrite(Lpos, 0);
         analogWrite(Lneg, leftSpeed);
     }
 
     int rightDirection = rightMotorDriver->getDir();
     int rightSpeed = rightMotorDriver->getSpeed();
 
     if (rightDirection == 1) {  // if direction is forward
        analogWrite(Rpos, rightSpeed);
        analogWrite(Rneg, 0);
     } else {                    // if direction is back
        analogWrite(Rpos, 0);
        analogWrite(Rneg, rightSpeed);
     }
 }