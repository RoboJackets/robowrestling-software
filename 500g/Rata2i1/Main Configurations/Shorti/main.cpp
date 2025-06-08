/**
 * Joe
 * File that outlines Shorti's main
 * 1/30/2025
 */

 #include <Arduino.h>

 // imports
 #include "motorDriver.h"
 #include "robotAction.h"
 #include "worldState.h"
 #include "Strategies.h"
 #include "lineReader.h"
 #include "irSensor.h"
 #include "Timer.h"
 
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
 #define Lline A0
 #define Rline A1
 #define switch1 A6
 #define switch2 A7
  
 // define objects
 motorDriver *leftMotorDriver;
 motorDriver *rightMotorDriver;
 worldState *state;
 robotAction *robot;
 Timer *timer;
 Strategies *strategies;
 
 
 
 // define functions
 void updateMotors();
 
 void setup() {
     // define pinmodes
     pinMode(Rpos, OUTPUT);
     pinMode(Rneg, OUTPUT);
     pinMode(Lpos, OUTPUT);
     pinMode(Lneg, OUTPUT);
     pinMode(StartMod, INPUT);
     pinMode(switch1, INPUT);
     pinMode(switch2, INPUT);
     pinMode(Lsensor, INPUT);
     pinMode(Rsensor, INPUT);
     pinMode(MSensor, INPUT);
     pinMode(Lline, INPUT);
     pinMode(Rline, INPUT);
     pinMode(Lside, INPUT);
     pinMode(Rside, INPUT);
     
 
     // instantiate objects
     leftMotorDriver = new motorDriver();
     rightMotorDriver = new motorDriver();
 
     //construct world state with struct
     worldState::joebotSensors sensors = {
         new lineReader(Lline),
         new lineReader(Rline),
         new lineReader(Lline),
         new lineReader(Rline),
         new IRSensor(Lsensor),
         new IRSensor(Rsensor),
         new IRSensor(Lside),
         new IRSensor(Rside),
         new IRSensor(MSensor)
     };
     
     state = new worldState(sensors);
 
     robot = new robotAction(leftMotorDriver, rightMotorDriver);
 
     timer = new Timer();
 
     strategies = new Strategies(state, robot, timer);
 
     Serial.begin(9600);
 
     // wait for start signal
     while (!digitalRead(StartMod)) {
       Serial.print(digitalRead(StartMod));
       Serial.println(" Waiting for start signal");
     }
 }
 
 /**
  * Polls all sensors and prints their values to the serial monitor
  * @param debug - if true, prints sensor values to the serial monitor
  */
 void pollSensors(bool debug = false) {
     int LsensorVal = digitalRead(Lsensor);
     int RsensorVal = digitalRead(Rsensor);
     int MSensorVal = digitalRead(MSensor);
     int LlineVal = digitalRead(Lline);
     int RlineVal = digitalRead(Rline);
     int LsideVal = digitalRead(Lside);
     int RsideVal = digitalRead(Rside);
     if (debug) {
         int switch1Val = digitalRead(switch1);
         int switch2Val = digitalRead(switch2);
 
         Serial.print("Lsensor: ");
         Serial.print(LsensorVal);
         Serial.print(" Rsensor: ");
         Serial.print(RsensorVal);
         Serial.print(" MSensor: ");
         Serial.print(MSensorVal);
         Serial.print(" Lline: ");
         Serial.print(LlineVal);
         Serial.print(" Rline: ");
         Serial.print(RlineVal);
         Serial.print(" Lside: ");
         Serial.print(LsideVal);
         Serial.print(" Rside: ");
         Serial.print(RsideVal);
         Serial.print(" switch1: ");
         Serial.print(switch1Val);
         Serial.print(" switch2: ");
         Serial.println(switch2Val);
     }
 }
 
 void brake() {
     robot -> stop();
 }
 
 void loop() {
     // pollSensors();
     // updateState()
     updateMotors();
     
     strategies->test();
 
     // listen for stop signal
     // if (!digitalRead(StartMod)) {
     //   while(true) {
     //     brake();
     //     Serial.println("braking");
     //   }
     // }
 
     // debug()
     
 }
 
 /**
  * Implemented for Shorti's motordrivers to conform to the
  * simple motordriver with speed and direction.  
  */ 
 void updateMotors() {
     int leftDirection = leftMotorDriver->getDirection();
     int leftSpeed = leftMotorDriver->getSpeed();
 
     if (leftDirection == 1) {  // if direction is forward
         analogWrite(Lpos, leftSpeed);
         analogWrite(Lneg, 0);
     } else {                    // if direction is back
         analogWrite(Lpos, 0);
         analogWrite(Lneg, leftSpeed);
     }
 
     int rightDirection = rightMotorDriver->getDirection();
     int rightSpeed = rightMotorDriver->getSpeed();
 
     if (rightDirection == 1) {  // if direction is forward
         analogWrite(Rpos, rightSpeed);
         analogWrite(Rneg, 0);
     } else {                    // if direction is back
         analogWrite(Rpos, 0);
         analogWrite(Rneg, rightSpeed);
     }
 }