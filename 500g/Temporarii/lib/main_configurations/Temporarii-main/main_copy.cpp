#include <Arduino.h>
#include "Sensors/WorldState.h"
#include "Robot/robotActions.hpp"
#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"

/*
* Temporarii main.cpp
*/

// Defining Pins
// #define name value
//OUTPUT Pins
#define LEFT_FRONT_MOTOR_PIN A1
#define RIGHT_FRONT_MOTOR_PIN A2
#define LEFT_REAR_MOTOR_PIN A3
#define RIGHT_REAR_MOTOR_PIN A4

//INPUT Pins
#define TOP_LEFT_LINE_PIN A10
#define TOP_RIGHT_LINE_PIN A11
#define BACK_LEFT_LINE_PIN A12
#define BACK_RIGHT_LINE_PIN A13
#define MID_IR_PIN A14
#define MIDLEFT_IR_PIN A15
#define MIDRIGHT_IR_PIN A16
#define LEFT_IR_PIN A17
#define RIGHT_IR_PIN A0

// Define Objects
IrSensor *left;
IrSensor *midLeft;
IrSensor *mid;
IrSensor *midRight;
IrSensor *right;
LineSensor *topLeftLine;
LineSensor *topRightLine;
LineSensor *backLeftLine;
LineSensor *backRightLine;

WorldState *world;

RobotActions *action;
MotorDriver *frontLeft;
MotorDriver *frontRight;
MotorDriver *backLeft;
MotorDriver *backRight;


Algorithm *strat;

RobotState *state;

void setup() {
  // Defines whether a pin is input or output
  pinMode(LEFT_FRONT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_REAR_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_FRONT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_REAR_MOTOR_PIN, OUTPUT);
  pinMode(TOP_LEFT_LINE_PIN, INPUT);
  pinMode(TOP_RIGHT_LINE_PIN, INPUT);
  pinMode(BACK_LEFT_LINE_PIN, INPUT);
  pinMode(BACK_RIGHT_LINE_PIN, INPUT);
  pinMode(MID_IR_PIN, INPUT);
  pinMode(MIDLEFT_IR_PIN, INPUT);
  pinMode(MIDRIGHT_IR_PIN, INPUT);
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);

  // Sensors
  left = new IrSensor();
  midLeft = new IrSensor();
  mid = new IrSensor();
  midRight = new IrSensor();
  right = new IrSensor();
  topLeftLine = new LineSensor();
  topRightLine = new LineSensor();
  backLeftLine = new LineSensor();
  backRightLine = new LineSensor();
  IrSensor *irArray[5] = {left, midLeft, mid, midRight, right};
  LineSensor *lineArray[4] = {topLeftLine, topRightLine, backLeftLine, backRightLine};
  // World State
  world = new WorldState(irArray, lineArray);
  // Robot Actions
  frontLeft = new MotorDriver();
  frontRight = new MotorDriver();
  backLeft = new MotorDriver();
  backRight = new MotorDriver();
  action = new RobotActions(frontLeft, frontRight, backLeft, backRight);
  // Robot State
  strat = new Algorithm(action);
  state = new RobotState(world, strat);
}

// put your main code here, to run repeatedly:
void loop() {
  pollSensors();
  calcState();
  writeMotors();
  debug();
}

void pollSensors() {
  topLeftLine->setValue(analogRead(TOP_LEFT_LINE_PIN));
  backLeftLine->setValue(analogRead(BACK_LEFT_LINE_PIN));
  topRightLine->setValue(analogRead(TOP_RIGHT_LINE_PIN));
  backRightLine->setValue(analogRead(BACK_RIGHT_LINE_PIN));

  left->setValue(digitalRead(LEFT_IR_PIN));
  midLeft->setValue(digitalRead(MIDLEFT_IR_PIN));
  mid->setValue(digitalRead(MID_IR_PIN));
  midRight->setValue(digitalRead(MIDRIGHT_IR_PIN));
  right->setValue(digitalRead(RIGHT_IR_PIN));
}

void debug() {
  Serial.print(millis());
  Serial.print("IR Sensor Value:");
  Serial.print(left->getValue());
  Serial.print(midLeft->getValue());
  Serial.print(mid->getValue());
  Serial.print(midRight->getValue());
  Serial.print(right->getValue());
  Serial.println();
  Serial.print("Line Sensor Value:");
  Serial.print(topLeftLine->getValue());
  Serial.print(backLeftLine->getValue());
  Serial.print(topRightLine->getValue());
  Serial.print(backRightLine->getValue());
  Serial.println();
}

void calcState() {
  // Calculate States
  state->runAlgorithm();
}

void writeMotors() {
  // Write to Motors digitalWrite()
  digitalWrite(LEFT_FRONT_MOTOR_PIN, frontLeft->getSpeed());
  digitalWrite(RIGHT_FRONT_MOTOR_PIN, frontRight->getSpeed());
  digitalWrite(LEFT_REAR_MOTOR_PIN, backLeft->getSpeed());
  digitalWrite(RIGHT_REAR_MOTOR_PIN, backRight->getSpeed());
}