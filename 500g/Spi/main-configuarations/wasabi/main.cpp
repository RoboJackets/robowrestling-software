/**
 * Kevin
 * V1.0
 * File that outlines Wasabi's main
 * 1/30/2025
 */

#include <Arduino.h>

// imports
#include "MotorDriver.h"

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

// object definitions
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;

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

    Serial.begin(9600);
}

void loop() {
    // pollsensors()
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

    if (leftDirection == 1) {  // if direction is forward
       analogWrite(L_POS, 1);
       analogWrite(L_NEG, 0);
    } else {                    // if direction is back
       analogWrite(L_POS, 0);
       analogWrite(L_NEG, 1);
    }

    int rightDirection = rightMotorDriver->getDirection();
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