/**
 * Xander
 * V1.0
 * File that outlines Spi's main
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
IRSensor *leftIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightIRSensor;
lineReader *leftlineReader;
lineReader *rightlineReader;

motorDriver *leftmotorDriver;
motorDriver *rightmotorDriver;
robotAction *robot;
worldState *state;
Strategies *strategies;
// RobotState *robotState;

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
  leftmotorDriver = new motorDriver();
  rightmotorDriver = new motorDriver();
  robot = new robotAction(leftmotorDriver, rightmotorDriver);
  leftIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftlineReader = new lineReader();
  rightlineReader = new lineReader();
  worldState::xanderSensors sensors = {
    leftlineReader,
    rightlineReader,
    leftIRSensor,
    rightIRSensor
  };
  state = new worldState(sensors);
  strategies = new Strategies(state, robot);
  // robotState = new RobotState(worldState, robotAction);

  // if (!DEBUGGING) {
  //   while (!digitalRead(START_PIN)) {
  //     Serial.print(digitalRead(START_PIN));
  //     Serial.println(" Waiting for start signal");
  //   }
  // }
}

void loop() {
  debug();          // method that just reads sensors and other values
  pollSensors();
  // calculateState();
  strategies->test();
  writeMotors();
  // if (!DEBUGGING) { // stops if recieves signal to stop from start module
  //   if (!digitalRead(START_PIN)) {
  //     while(true) {
  //       // robotAction->brake();
  //       Serial.println("braking");
  //     }
  //   }
  // }
}

 /**
  * Implemented for Spi's motorDrivers to conform to the
  * simple motorDriver with speed and direction. 
  * (Spi's motorDrivers conform to this by default)  
  */ 
void writeMotors() {
  analogWrite(RIGHT_PWM, rightmotorDriver->getSpeed());
  digitalWrite(RIGHT_DIR, rightmotorDriver->getDirection());
  analogWrite(LEFT_PWM, leftmotorDriver->getSpeed());
  digitalWrite(LEFT_DIR, leftmotorDriver->getDirection());
}

/**
 * method to update the sensor objects
 */
void pollSensors() {
  leftIRSensor->setValue(digitalRead(LEFT_IR));
  middleIRSensor->setValue(digitalRead(MIDDLE_IR));
  rightIRSensor->setValue(digitalRead(RIGHT_IR));
  leftlineReader->setValue(analogRead(LEFT_LINE));
  rightlineReader->setValue(analogRead(RIGHT_LINE));
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
    Serial.print(rightmotorDriver->getSpeed());
    Serial.print(rightmotorDriver->getDirection());
    Serial.print(leftmotorDriver->getSpeed());
    Serial.print(leftmotorDriver->getDirection());
  }
  Serial.println();
}