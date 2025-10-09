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
#include "Sensors/WorldState.hpp"
#include "Sensors/irSensor.h"
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
LineSensor *test5;
LineSensor *test6;

MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
MotorDriver *test1;
MotorDriver *test2;
RobotActions *robotAction;
WorldState *worldState;
RobotState *robotState;
Algorithm *algo;
// if debugging is true it will skip the start module check.
const bool DEBUGGING = true;

// function definitions
void debug();
void writeMotors();
void pollSensors();
void calculateState();

// instantiation
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting Setup");

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

  leftIRSensor = new IrSensor();
  middleIRSensor = new IrSensor();
  rightIRSensor = new IrSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();

  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();

  test1 = new MotorDriver();
  test2 = new MotorDriver();
  test3 = new IrSensor();
  test4 = new IrSensor();
  test5 = new LineSensor();
  test6 = new LineSensor();

  IrSensor *irSensors[5] = {test3, leftIRSensor, middleIRSensor, rightIRSensor, test4};
  LineSensor *lineSensors[4] = {leftLineSensor, test5, rightLineSensor, test6};
  robotAction = new RobotActions(leftMotorDriver, rightMotorDriver, test1, test2);
  worldState = new WorldState(irSensors, lineSensors);
  algo = new Algorithm(robotAction);
  robotState = new RobotState(worldState, algo);

  if (!DEBUGGING)
  {
    while (!digitalRead(START_PIN))
    {
      Serial.print(digitalRead(START_PIN));
      Serial.println(" Waiting for start signal");
    }
  }
}

void loop()
{
  // Serial.println("Starting loop");
  /*
   debug();          // method that just reads sensors and other values
   pollSensors();
   if (!DEBUGGING) { // stops if recieves signal to stop from start module
     if (!digitalRead(START_PIN)) {
       while(true) {
         //robotAction->brake();
         Serial.println("braking");
       }
     }
   }
     */

  pollSensors();
  calculateState();
  writeMotors();
}

/**
 * Implemented for Spi's motordrivers to conform to the
 * simple motordriver with speed and direction.
 * (Spi's motordrivers conform to this by default)
 */
void writeMotors()
{
  // int rightSpeed = rightMotorDriver->getSpeed();
  // int rightDirection = rightMotorDriver->getDirection();
  // rightMotorDriver->setSpeed(100);
  // rightMotorDriver->setDirection(0);
  // leftMotorDriver->setSpeed(100);
  // leftMotorDriver->setDirection(0);
  Serial.println("Testing");
  Serial.print("Right Speed: ");
  Serial.println(rightMotorDriver->getSpeed());
  // delay(2000);
  analogWrite(RIGHT_PWM, rightMotorDriver->getSpeed());
  digitalWrite(RIGHT_DIR, rightMotorDriver->getDirection());
  analogWrite(LEFT_PWM, leftMotorDriver->getSpeed());
  digitalWrite(LEFT_DIR, leftMotorDriver->getDirection());
  // 0 = backward, 1 = forward
  // analogWrite(RIGHT_PWM, 100);
  // digitalWrite(RIGHT_DIR, 1);
  // analogWrite(RIGHT_PWM, 100);
  // digitalWrite(RIGHT_DIR, 0);
  // analogWrite(LEFT_PWM, 100);
  // digitalWrite(LEFT_DIR, 0);
}

/**
 * method to update the sensor objects
 */
void pollSensors()
{
  // delay(500);
  leftIRSensor->setValue(digitalRead(LEFT_IR));
  middleIRSensor->setValue(digitalRead(MIDDLE_IR));
  rightIRSensor->setValue(digitalRead(RIGHT_IR));
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
  // Serial.print("Mid IR: ");
  // Serial.println(middleIRSensor->getValue());
}

/**
 * Calc State using algorithm
 */
void calculateState()
{
  robotState->runAlgorithm();
}

/**
 * method that reads simple sensor and motor values
 */
void debug()
{
  if (true)
  {
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
  if (true)
  {
    Serial.print(rightMotorDriver->getSpeed());
    Serial.print(rightMotorDriver->getDirection());
    Serial.print(leftMotorDriver->getSpeed());
    Serial.print(leftMotorDriver->getDirection());
  }
  Serial.println();
}