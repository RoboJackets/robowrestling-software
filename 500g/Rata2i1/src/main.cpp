
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
#define LF_IR 2;
#define RF_IR 3;
#define LB_IR 4;
#define RB_IR 5;
#define LF_LINE 0;
// #define RF_LINE -1
// #define LB_LINE -1;
#define RB_LINE 1;
#define R_PWM 6;
#define R_PWM 9;
//switch and startmod?
#define StartMod -1;
#define Switch0 -1;
#define Switch1 -1;

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
 

// define objects
IRSensor *leftFrontIR;
IRSensor *rightFrontIR;
IRSensor *leftBackIR;
IRSensor *rightBackIR;
lineReader *leftFrontLine;
lineReader *rightFrontLine;
lineReader *leftBackLine;
lineReader *rightBackLine;

motorDriver *leftMotorDriver;
motorDriver *rightMotorDriver;
robotAction *robot;
worldState *state;
Timer *timer;
Strategies *strategies;



// define functions
void updateMotors();

void setup() {
    // define pinmodes
    pinMode(LF_LINE, INPUT);
    pinMode(RB_LINE, INPUT);
    pinMode(LF_IR, INPUT);
    pinMode(RF_IR, INPUT);
    pinMode(LB_IR, INPUT);
    pinMode(RB_IR, INPUT);
    
    lineReader LFLine = new lineReader(LF_LINE);
    lineReader RBLine = new lineReader(RB_LINE);
    IRSensor LFIR = new IRSensor(LF_IR);
    IRSensor RFIR = new IRSensor(RF_IR);
    IRSensor LBIR = new IRSensor(LB_IR);
    IRSensor RBIR = new IRSensor(RB_IR);

    // instantiate objects
    leftMotorDriver = new motorDriver();
    rightMotorDriver = new motorDriver();

    worldState::robotSensors sensors = {
        LFLine,
        RFLine,
        LBLine,
        RBLine,
        LFIR,
        RFIR,
        LBIR,
        RBIR
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
    LFLine->setValue(digitalRead(LF_LINE));
    RFLine->setValue(digitalRead(RF_LINE));
    LBLine->setValue(digitalRead(LB_LINE));
    RBLine->setValue(digitalRead(RB_LINE));
    LFIR->setValue(digitalRead(LF_LINE));
    RFIR->setValue(digitalRead(RF_LINE));
    LBIR->setValue(digitalRead(LB_LINE));
    RBIR->setValue(digitalRead(RB_LINE));
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
 // pinouts
 #define LF_IR -1;
 #define RF_IR -1;
 #define LB_IR -1;
 #define RB_IR -1;
 #define LF_LINE -1;
 #define RF_LINE -1l
 #define LB_LINE -1;
 #define RB_LINE -1;
 //switch and startmod?
 #define StartMod -1;
 #define Switch0 -1;
 #define Switch1 -1;
 
 
  
 // define objects
 IRSensor *leftFrontIR;
 IRSensor *rightFrontIR;
 IRSensor *leftBackIR;
 IRSensor *rightBackIR;
 lineReader *leftFrontLine;
 lineReader *rightFrontLine;
 lineReader *leftBackLine;
 lineReader *rightBackLine;
 
 motorDriver *leftMotorDriver;
 motorDriver *rightMotorDriver;
 robotAction *robot;
 worldState *state;
 Timer *timer;
 Strategies *strategies;
 
 
 
 // define functions
 void updateMotors();
 
 void setup() {
     // define pinmodes
     pinMode(LF_LINE, INPUT);
     pinMode(RF_LINE, INPUT);
     pinMode(LB_LINE, INPUT);
     pinMode(RB_LINE, INPUT);
     pinMode(LF_IR, INPUT);
     pinMode(RF_IR, INPUT);
     pinMode(LB_IR, INPUT);
     pinMode(RB_IR, INPUT);
     
     lineReader LFLine = new lineReader(LF_LINE);
     lineReader RFLine = new lineReader(RF_LINE);
     lineReader LBLine = new lineReader(LB_LINE);
     lineReader RBLine = new lineReader(RB_LINE);
     IRSensor LFIR = new IRSensor(LF_IR);
     IRSensor RFIR = new IRSensor(RF_IR);
     IRSensor LBIR = new IRSensor(LB_IR);
     IRSensor RBIR = new IRSensor(RB_IR);
 
     // instantiate objects
     leftMotorDriver = new motorDriver();
     rightMotorDriver = new motorDriver();
 
     worldState::robotSensors sensors = {
         LFLine,
         RFLine,
         LBLine,
         RBLine,
         LFIR,
         RFIR,
         LBIR,
         RBIR
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
     LFLine->setValue(digitalRead(LF_LINE));
     RFLine->setValue(digitalRead(RF_LINE));
     LBLine->setValue(digitalRead(LB_LINE));
     RBLine->setValue(digitalRead(RB_LINE));
     LFIR->setValue(digitalRead(LF_LINE));
     RFIR->setValue(digitalRead(RF_LINE));
     LBIR->setValue(digitalRead(LB_LINE));
     RBIR->setValue(digitalRead(RB_LINE));
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
