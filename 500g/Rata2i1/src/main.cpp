
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
#define F_LINE 1;
#define B_LINE 2;
#define R_PWM 6;
#define L_PWM 9;
#define R_FWD 19;
#define R_BWD 20;
#define L_FWD 21;
#define L_BWD 22;
#define StartMod -1;
#define Switch0 -1;
#define Switch1 -1;

// define objects
IRSensor *leftFrontIR;
IRSensor *rightFrontIR;
IRSensor *leftBackIR;
IRSensor *rightBackIR;
lineReader *frontLine;
lineReader *backLine;

motorDriver *leftMotorDriver;
motorDriver *rightMotorDriver;
robotAction *robot;
worldState *state;
Timer *timer;
Strategies *strategies;

// define functions
void updateMotors();

void setup()
{
    // define pinmodes
    pinMode(LF_IR, INPUT);
    pinMode(RF_IR, INPUT);
    pinMode(LB_IR, INPUT);
    pinMode(RB_IR, INPUT);
    pinMode(F_LINE, INPUT);
    pinMode(B_LINE, INPUT);

    worldState::robotSensors sensors = {
        new lineReader(F_LINE),
        new lineReader(B_LINE),
        new IRSensor(LF_IR),
        new IRSensor(RF_IR),
        new IRSensor(LB_IR),
        new IRSensor(RB_IR)};
    state = new worldState(sensors);

    robot = new robotAction(leftMotorDriver, rightMotorDriver);

    timer = new Timer();

    strategies = new Strategies(state, robot, timer);

    Serial.begin(9600);

    // wait for start signal
    while (!digitalRead(StartMod))
    {
        Serial.print(digitalRead(StartMod));
        Serial.println(" Waiting for start signal");
    }
}

/**
 * Polls all sensors and prints their values to the serial monitor
 * @param debug - if true, prints sensor values to the serial monitor
 */
void pollSensors(bool debug = false)
{
    LFLine->setValue(digitalRead(LF_LINE));
    RFLine->setValue(digitalRead(RF_LINE));
    LBLine->setValue(digitalRead(LB_LINE));
    RBLine->setValue(digitalRead(RB_LINE));
    LFIR->setValue(digitalRead(LF_LINE));
    RFIR->setValue(digitalRead(RF_LINE));
    LBIR->setValue(digitalRead(LB_LINE));
    RBIR->setValue(digitalRead(RB_LINE));
}

void brake()
{
    robot->stop();
}

void loop()
{
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

