/**
 * Joe
 * V1.1
 * File that outlines Pooki's main
 * 1/30/2025
 */

#include <Arduino.h>
#include <Servo.h>

// imports
#include "MotorDriver.h"

// pinouts
const int LEFT_IR_90 = 12;
const int LEFT_IR_45 = 7;
const int RIGHT_IR_90 = 8;
const int RIGHT_IR_45 = 2;
const int MIDDLE_IR = 7;
const int START_MODULE = 10;
const int R_POS = 5;
const int R_NEG = 3;
const int L_POS = 11;
const int L_NEG = 6;
const int DIP_SWITCH_1 = A6;
const int DIP_SWITCH_2 = A7;

// define objects
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
Servo servo;

void updateMotors();

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
    pinMode(START_MODULE, INPUT);
    pinMode(DIP_SWITCH_1, INPUT);
    pinMode(DIP_SWITCH_2, INPUT);

    Serial.begin(9600);
    servo.attach(9);
}

void loop() {
    // pollsensors()
    // updateState()
    updateMotors();
    // listen for stop signal
    // debug() 
}

/**
 * Implemented for Pooki's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
    int leftDirection = leftMotorDriver->getDirection();
    int leftSpeed = leftMotorDriver->getSpeed();

    if (leftDirection == 1) {  // if direction is forward
        analogWrite(L_POS, leftSpeed);
        analogWrite(L_NEG, 0);
    } else {                    // if direction is back
        analogWrite(L_POS, 0);
        analogWrite(L_NEG, leftSpeed);
    }

    int rightDirection = rightMotorDriver->getDirection();
    int rightSpeed = rightMotorDriver->getSpeed();

    if (rightDirection == 1) {  // if direction is forward
        analogWrite(R_POS, rightSpeed);
        analogWrite(R_NEG, 0);
    } else {                    // if direction is back
        analogWrite(R_POS, 0);
        analogWrite(R_NEG, rightSpeed);
    }
}