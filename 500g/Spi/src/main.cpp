#include <Arduino.h>
#include <Wire.h>

#include "RobotAction.h"
#include "MotorDriver.h"
#include "WorldState.h"
#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"
#include "RobotState.h"
#include "algorithms/InchForward.hpp"
#include "algorithms/Shape.hpp"
#include "algorithms/Tracker.hpp"
#include "algorithms/Scan.hpp"

const int START_PIN = 0;
const int RIGHT_IN1 = 5;
const int RIGHT_IN2 = 6;
const int LEFT_IN1 = 7;
const int LEFT_IN2 = 8;
const int KILL_SW = 1;
const int LEFT_IR = 2;
const int MIDDLE_IR = 3;
const int RIGHT_IR = 4;
const int LEFT_LINE = 23;
const int RIGHT_LINE = 22;
const int DIP_1 = 20;
const int DIP_2 = 21;
// sensors

IRSensor *leftIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;

// robot stuff
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotAction *robotAction;
WorldState *worldState;
RobotState *robotState;
InchForward *inchForward;
Shape *shape;
Tracker *tracker;
Scan *scan;
BackSpin *backSpinLeft;

const bool DEBUGGING = false;

void debug();
void writeMotors();
void pollSensors();
void calculateState(int time);
void calibrateLineSensors();

void setup() {
  Serial.begin(9600);

  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);

  pinMode(LEFT_IR, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_LINE, INPUT);
  pinMode(RIGHT_LINE, INPUT);
  pinMode(START_PIN, INPUT);
  
  int mode = (digitalRead(DIP_1) * 2) + (digitalRead(DIP_2));

  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();
  robotAction = new RobotAction(leftMotorDriver, rightMotorDriver, 40);
  leftIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();
  worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, middleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotAction);
  inchForward = new InchForward(worldState, robotAction, 128);
  shape = new Shape(worldState, robotAction);
  tracker = new Tracker(worldState, robotAction, mode);
  scan = new Scan(robotAction);
  backSpinLeft = new BackSpin(robotAction, true);
  
  leftLineSensor->setThreshold(900);
  rightLineSensor->setThreshold(900);

  if (!DEBUGGING) {
    while (!digitalRead(START_PIN)) {
      Serial.print(digitalRead(START_PIN));
      Serial.println(" Waiting for start signal");
      // calibrateLineSensors();
    }
  }
  robotState->setStartTimer(millis());
}

void loop() {
  debug();
  pollSensors();
  calculateState(millis());
  writeMotors();
  if (!DEBUGGING) {
    if (!digitalRead(START_PIN)) {
      while(true) {
        robotAction->brake();
        writeMotors();
        Serial.println("braking");
      }
    }
  }
}

void writeMotors() {
  analogWrite(RIGHT_IN1, rightMotorDriver->getIn1());
  analogWrite(RIGHT_IN2, rightMotorDriver->getIn2());
  analogWrite(LEFT_IN1, leftMotorDriver->getIn1());
  analogWrite(LEFT_IN2, leftMotorDriver->getIn2());
}

void pollSensors() {
  //implement proper velocity measurement D:
  leftIRSensor->setValue(digitalRead(LEFT_IR), millis()); // bro the teensy is cracked it does like 50 polls in like 1ms
  middleIRSensor->setValue(digitalRead(MIDDLE_IR), millis());
  rightIRSensor->setValue(digitalRead(RIGHT_IR), millis());
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
}

void calculateState(int time) {
  tracker->run();
  // backSpinLeft->run();
}

void calibrateLineSensors() {
  leftLineSensor->calibrate(analogRead(LEFT_LINE));
  rightLineSensor->calibrate(analogRead(RIGHT_LINE));
}

void debug() {
  if (true) {
    Serial.print(millis());
    Serial.print(": ");
  }
  if (false) {
    Serial.print(leftMotorDriver->getIn1());
    Serial.print(leftMotorDriver->getIn2());
    Serial.print(" ");
    Serial.print(rightMotorDriver->getIn1());
    Serial.print(rightMotorDriver->getIn2());
    Serial.print(" ");
  }
  if (true) {
    Serial.print(digitalRead(START_PIN));
    Serial.print(" ");
    Serial.print(leftIRSensor->getValue());
    Serial.print(middleIRSensor->getValue());
    Serial.print(rightIRSensor->getValue());
    Serial.print(" ");
    Serial.print(digitalRead(LEFT_IR));
    Serial.print(digitalRead(MIDDLE_IR));
    Serial.print(digitalRead(RIGHT_IR));
    Serial.print(" ");
    // Serial.print(rightIRSensor->getSum());
    // Serial.print(" ");
    Serial.print(analogRead(LEFT_LINE));
    Serial.print(" ");
    Serial.print(analogRead(RIGHT_LINE));
    Serial.print(" ");
  }
  if (true) {
    Serial.print(rightMotorDriver->getIn1());
    Serial.print(rightMotorDriver->getIn2());
    Serial.print(leftMotorDriver->getIn1());
    Serial.print(leftMotorDriver->getIn2());
  }
  if (false) {
    Serial.print(leftLineSensor->getValue());
    // Serial.print(leftLineSensor->getThreshold());
    Serial.print(rightLineSensor->getValue());
    // Serial.print(leftLineSensor->getThreshold());
    Serial.print((int)worldState->getPosition());
  }
  if (true) {
    Serial.print(" ");
    Serial.print((int)worldState->getPosition());
  }
  Serial.println();
}