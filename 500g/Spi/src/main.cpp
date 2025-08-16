#include <Arduino.h>
#include <Wire.h>

#include "sensors/Accelerometer.h"
#include "RobotAction.h"
#include "MotorDriver.h"
#include "WorldState.h"
#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"
#include "RobotState.h"
#include "Timer.h"
#include "algorithms/InchForward.hpp"
#include "algorithms/BackSpin.hpp"
#include "algorithms/BackSpinLeft.hpp"

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
// sensors

Velocity *velocity;
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
BackSpinLeft *backSpinLeft;

//etc
Timer *accelerometerTimer;
Timer *debugTimer;

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
  
  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();
  robotAction = new RobotAction(leftMotorDriver, rightMotorDriver, 40);
  velocity = new Velocity();
  leftIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();
  worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, middleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotAction);
  accelerometerTimer = new Timer();
  debugTimer = new Timer();
  inchForward = new InchForward(worldState, robotAction, 128);
  backSpinLeft = new BackSpinLeft(robotAction);
  
  debugTimer->setTimeInterval(10000);

  leftLineSensor->setThreshold(800);
  rightLineSensor->setThreshold(800);

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
  leftIRSensor->setValue(digitalRead(LEFT_IR), 50); // bro the teensy is cracked it does like 50 polls in like 1ms
  middleIRSensor->setValue(digitalRead(MIDDLE_IR), 50);
  rightIRSensor->setValue(digitalRead(RIGHT_IR), 50);
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
}

void calculateState(int time) {
  // robotState->calculateState(time);
  backSpinLeft->run();
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
  if (false) {
    Serial.print(velocity->getX()); 
    Serial.print(" ");
    Serial.print(velocity->getY()); // -1000 = forward accel
    Serial.print(" ");
    Serial.print(velocity->getZ()); // up / down
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
  if (false) {
    Serial.print((int)worldState->getLastEnemyPosition());
  }
  Serial.println();
}