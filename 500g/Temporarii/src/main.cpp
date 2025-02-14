/**
 * Xander
 * V1.0
 * File that outlines Spi's main
 * 1/30/2025
 */

 #include <Arduino.h>

 // imports
 #include "Robot/robotActions.hpp"
 #include "Robot/motorDriver.hpp"
 #include "Sensors/WorldState.h"
 #include "Sensors/IrSensor.h"
 #include "Sensors/lineSensor.h"
 #include "Robot/robotState.hpp"
 
 // pinouts
 const int RIGHT_PWM = 6;
 const int RIGHT_DIR = 5;
 const int LEFT_PWM = 8;
 const int LEFT_DIR = 7;
 const int LEFT_IR = 2;
 const int MIDDLE_IR = 3;
 const int RIGHT_IR = 4;
 const int LEFT_LINE = A8;
 const int RIGHT_LINE = A9;
 const int START_PIN = 34;
 
 // object definitions
 IrSensor *leftIRSensor;
 IrSensor *middleIRSensor;
 IrSensor *rightIRSensor;
 LineSensor *leftLineSensor;
 LineSensor *rightLineSensor;
 IrSensor *test3;
 IrSensor *test4;
 
 MotorDriver *leftMotorDriver;
 MotorDriver *rightMotorDriver;
 MotorDriver *test1;
 MotorDriver *test2;
 RobotActions *robotAction;
 WorldState *worldState;
 RobotState *robotState;
 
 // if debugging is true it will skip the start module check.
 const bool DEBUGGING = false;
 
 // function definitions
 void debug();
 void writeMotors();
 void pollSensors();
 
 void setup() {
   Serial.begin(9600);
   
   // pinmode definitions
   pinMode(RIGHT_PWM, OUTPUT);
   pinMode(RIGHT_DIR, OUTPUT);
   pinMode(LEFT_PWM, OUTPUT);
   pinMode(LEFT_DIR, OUTPUT);
 
   pinMode(LEFT_IR, INPUT);
   pinMode(MIDDLE_IR, INPUT);
   pinMode(RIGHT_IR, INPUT);
   pinMode(LEFT_LINE, INPUT);
   pinMode(RIGHT_LINE, INPUT);
   pinMode(START_PIN, INPUT);
   
   // instantion
   leftMotorDriver = new MotorDriver();
   rightMotorDriver = new MotorDriver();
   robotAction = new RobotActions(leftMotorDriver, rightMotorDriver, test1, test2);
   leftIRSensor = new IrSensor();
   middleIRSensor = new IrSensor();
   rightIRSensor = new IrSensor();
   leftLineSensor = new LineSensor();
   rightLineSensor = new LineSensor();
   IrSensor *irSensors = new IrSensor[5];
   {test3, leftIRSensor, middleIRSensor, rightIRSensor, test4};
   LineSensor *lineSensors = {leftLineSensor, rightLineSensor}
   worldState = new WorldState(irSensors, lineSensors);
   robotState = new RobotState(worldState, robotAction);
 
   if (!DEBUGGING) {
     while (!digitalRead(START_PIN)) {
       Serial.print(digitalRead(START_PIN));
       Serial.println(" Waiting for start signal");
     }
   }
 }
 
 void loop() {
   debug();          // method that just reads sensors and other values
   pollSensors();
   // calculateState();
   writeMotors();
   if (!DEBUGGING) { // stops if recieves signal to stop from start module
     if (!digitalRead(START_PIN)) {
       while(true) {
         //robotAction->brake();
         Serial.println("braking");
       }
     }
   }
 }
 
  /**
   * Implemented for Spi's motordrivers to conform to the
   * simple motordriver with speed and direction. 
   * (Spi's motordrivers conform to this by default)  
   */ 
 void writeMotors() {
   analogWrite(RIGHT_PWM, rightMotorDriver->getSpeed());
   digitalWrite(RIGHT_DIR, rightMotorDriver->getDirection());
   analogWrite(LEFT_PWM, leftMotorDriver->getSpeed());
   digitalWrite(LEFT_DIR, leftMotorDriver->getDirection());
 }
 
 /**
  * method to update the sensor objects
  */
 void pollSensors() {
   leftIRSensor->setValue(digitalRead(LEFT_IR));
   middleIRSensor->setValue(digitalRead(MIDDLE_IR));
   rightIRSensor->setValue(digitalRead(RIGHT_IR));
   leftLineSensor->setValue(analogRead(LEFT_LINE));
   rightLineSensor->setValue(analogRead(RIGHT_LINE));
 }
 
 /**
  * method that reads simple sensor and motor values
  */
 void debug() {
   if (true) {
     Serial.print(digitalRead(START_PIN));
     Serial.print(" ");
     Serial.print(leftIRSensor->getValue());
     Serial.print(middleIRSensor->getValue());
     Serial.print(rightIRSensor->getValue());
     Serial.print(" ");
     Serial.print(analogRead(LEFT_LINE));
     Serial.print(" ");
     Serial.print(analogRead(RIGHT_LINE));
     Serial.print(" ");
   }
   if (true) {
     Serial.print(rightMotorDriver->getSpeed());
     Serial.print(rightMotorDriver->getDirection());
     Serial.print(leftMotorDriver->getSpeed());
     Serial.print(leftMotorDriver->getDirection());
   }
   Serial.println();
 }