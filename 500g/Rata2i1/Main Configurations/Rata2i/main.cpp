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
    
    

    // instantiate objects
    leftMotorDriver = new motorDriver();
    rightMotorDriver = new motorDriver();

    worldState::robotSensors sensors = {
        new lineReader(LF_LINE),
        new lineReader(RF_LINE),
        new lineReader(LB_LINE),
        new lineReader(RB_LINE),
        new IRSensor(LF_IR),
        new IRSensor(RF_IR),
        new IRSensor(LB_IR),
        new IRSensor(RB_IR)
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