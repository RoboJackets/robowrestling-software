#include <Arduino.h>
#include <IRSensor.h>
#include <LineSensor.h>
#include <MotorDriver.h>
#include <RobotActions.h>
#include <WorldState.h>
#include <RobotState.h>

IRSensor *leftIRSensor;
IRSensor *leftMiddleIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightMiddleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotActions *robotActions;
WorldState *worldState;
RobotState *robotState;

// --- Pin definitions ---
const int LEFT_IR_90  = 3;
const int LEFT_IR_45  = 4;
const int RIGHT_IR_90 = 8;
const int RIGHT_IR_45 = 6;
const int MIDDLE_IR   = 5;
const int START_MODULE= 2;
const int R_POS = 0;   // move to PWM pins if needed
const int R_NEG = 1;
const int L_POS = 29;
const int L_NEG = 28;
const int LEFT_LINE  = A7;
const int RIGHT_LINE = A6;

// --- Start control ---
bool started = false;

void setup() {
  // Serial.begin(9600);
  pinMode(R_POS, OUTPUT);
  pinMode(R_NEG, OUTPUT);
  pinMode(L_POS, OUTPUT);
  pinMode(L_NEG, OUTPUT);
  pinMode(LEFT_IR_90, INPUT);
  pinMode(LEFT_IR_45, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR_45, INPUT);
  pinMode(RIGHT_IR_90, INPUT);
  pinMode(LEFT_LINE, INPUT);
  pinMode(RIGHT_LINE, INPUT);
  pinMode(START_MODULE, INPUT);  // use INPUT_PULLUP if switch pulls low

  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();
  robotActions = new RobotActions(leftMotorDriver, rightMotorDriver);
  leftIRSensor = new IRSensor();
  leftMiddleIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightMiddleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();

  worldState = new WorldState(leftLineSensor, rightLineSensor,
                              leftIRSensor, leftMiddleIRSensor,
                              middleIRSensor, rightMiddleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotActions, leftMotorDriver, rightMotorDriver);

  robotActions->drive(0, 0);  // stop motors initially
}

void updateMotors() {
  int leftDirection = leftMotorDriver->getDirection();
  int leftSpeed = leftMotorDriver->getSpeed();
  if (leftDirection == 1) {
    analogWrite(L_POS, leftSpeed);
    analogWrite(L_NEG, 0);
  } else {
    analogWrite(L_POS, 0);
    analogWrite(L_NEG, leftSpeed);
  }

  int rightDirection = rightMotorDriver->getDirection();
  int rightSpeed = rightMotorDriver->getSpeed();
  if (rightDirection == 1) {
    analogWrite(R_POS, rightSpeed);
    analogWrite(R_NEG, 0);
  } else {
    analogWrite(R_POS, 0);
    analogWrite(R_NEG, rightSpeed);
  }
}

void pollSensors() {
  leftIRSensor->setValue(digitalRead(LEFT_IR_90));
  middleIRSensor->setValue(digitalRead(MIDDLE_IR));
  rightIRSensor->setValue(digitalRead(RIGHT_IR_90));
  leftMiddleIRSensor->setValue(digitalRead(LEFT_IR_45));
  rightMiddleIRSensor->setValue(digitalRead(RIGHT_IR_45));
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
}

void calculateState(int time) {
  robotState->calculateState(time);
}

void loop() {
  // If start module is LOW, stop immediately
  if (digitalRead(START_MODULE) == LOW) {
    robotActions->drive(0, 0);
    started = false;  // reset start state
    return;
  }

  // When it first goes HIGH, wait 5 seconds before starting
  if (!started) {
    delay(5000);  // 5-second start delay
    started = true;
  }

  // Normal operation
  pollSensors();
  calculateState(millis());
  updateMotors();
}
