/**
 * Joe
 * File that outlines Shorti's main
 * 1/30/2025
 */

#include <Arduino.h>

// imports
#include "../../Oni/include/motor/motor_driver.h"

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

    // wait for start signal
    while (!digitalRead(StartMod)) {
      Serial.print(digitalRead(StartMod));
      Serial.println(" Waiting for start signal");
    }
}

void loop() {
    // pollsensors()
    // updateState()
    updateMotors();

    // listen for stop signal
    if (!digitalRead(StartMod)) {
      while(true) {
        // brake()
        Serial.println("braking");
      }
    }
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