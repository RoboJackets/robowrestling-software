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

//!! TBD
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

void setup() {
  Serial.begin(9600);

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

  worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, leftMiddleIRSensor, middleIRSensor, rightMiddleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotActions);

}

void loop() {
    writeMotors();
    calculateState();
}

void writeMotors() {
  analogWrite(RIGHT_PWM, rightMotorDriver->getSpeed());
  digitalWrite(RIGHT_DIR, rightMotorDriver->getDirection());
  analogWrite(LEFT_PWM, leftMotorDriver->getSpeed());
  digitalWrite(LEFT_DIR, leftMotorDriver->getDirection());
}

void calculateState() {
  robotState->calculateState();
}