/**
 * Joe
 * V1.1
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
 const int LEFT_IR_90 = 12;
 const int LEFT_IR_45 = 8;
 const int RIGHT_IR_90 = 2;
 const int RIGHT_IR_45 = 4;
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
 motorDriver *leftMotorDriver;
 motorDriver *rightMotorDriver;
 worldState *state;
 robotAction *robot;
 Timer *timer;
 Strategies *strategies;

 //sensors
lineReader *leftLine;
lineReader *rightLine;
IRSensor *leftIR90;
IRSensor *rightIR90;
IRSensor *leftIR45;
IRSensor *rightIR45;
 
 void updateMotors();
 
 void setup() {
     // define pinmodes
     pinMode(R_POS, OUTPUT);
     pinMode(R_NEG, OUTPUT);
     pinMode(L_POS, OUTPUT);
     pinMode(L_NEG, OUTPUT);
     pinMode(LEFT_IR_90, INPUT);
     pinMode(LEFT_IR_45, INPUT);
     pinMode(RIGHT_IR_45, INPUT);
     pinMode(RIGHT_IR_90, INPUT);
     pinMode(LEFT_LINE, INPUT);
     pinMode(RIGHT_LINE, INPUT);
     pinMode(START_MODULE, INPUT);
     pinMode(DIP_SWITCH_1, INPUT);
     pinMode(DIP_SWITCH_2, INPUT);

     // instantiate objects
     leftMotorDriver = new motorDriver();
     rightMotorDriver = new motorDriver();

     // instantiate lineReader and IRSensor objects
      leftLine = new lineReader(LEFT_LINE);
      rightLine = new lineReader(RIGHT_LINE);
      leftIR90 = new IRSensor(LEFT_IR_90);
      rightIR90 = new IRSensor(RIGHT_IR_90);
      leftIR45 = new IRSensor(LEFT_IR_45);
      rightIR45 = new IRSensor(RIGHT_IR_45);
 
     //construct world state with struct
     worldState::joebotSensors sensors = {
         leftLine,
         rightLine,
         leftIR90,
         rightIR90,
         leftIR45,
         rightIR45
     };
     
     state = new worldState(sensors);
 
     robot = new robotAction(leftMotorDriver, rightMotorDriver);
 
     timer = new Timer();
 
     strategies = new Strategies(state, robot, timer);
 
     Serial.begin(9600);
 }
 
 void loop() {
     pollSensors();
     // updateState()
     updateMotors();
     // listen for stop signal
     // debug() 
 }
 
 /**
  * Implemented for Shorti's motordrivers to conform to the
  * simple motordriver with speed and direction.  
  */ 
 void updateMotors() {
     int leftDirection = leftMotorDriver->getDirection();
     int leftSpeed = leftMotorDriver->getSpeed();
 
   //   if (leftDirection == 1) {  // if direction is forward
   //      analogWrite(L_POS, 255);
   //      analogWrite(L_NEG, 0);
   //   } else {                    // if direction is back
   //      analogWrite(L_POS, 0);
   //      analogWrite(L_NEG, 255);
   //   }
 
     int rightDirection = rightMotorDriver->getDirection();
     int rightSpeed = rightMotorDriver->getSpeed();
 
   //   if (rightDirection == 1) {  // if direction is forward
   //      analogWrite(R_POS, 255);
   //      analogWrite(R_NEG, 0);
   //   } else {                    // if direction is back
   //      analogWrite(R_POS, 0);
   //      analogWrite(R_NEG, 255);
   //   }

   //   // controls the speed
     analogWrite(L_PWM, leftSpeed);
     analogWrite(R_PWM, rightSpeed);
 }

 void pollSensors() {
   leftLine->setValue(digitalRead(LEFT_LINE));
   rightLine->setValue(digitalRead(RIGHT_LINE));
   leftIR90->setValue(digitalRead(LEFT_IR_90));
   rightIR90->setValue(digitalRead(RIGHT_IR_90));
   leftIR45->setValue(digitalRead(LEFT_IR_45));
   rightIR45->setValue(digitalRead(RIGHT_IR_45));
 }

   void updateState() {
      //save enemy position
      Position enemyPosition = state->getEnemyPosition();
      Position position = state->getPosition();
   }