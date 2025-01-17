#include <Arduino.h>
#include <IRSensor.h>
#include <LineSensor.h>
#include <MotorDriver.h>
#include <RobotActions.h>
#include <WorldState.h>

IRSensor *leftIRSensor;
IRSensor *leftMiddleIRSensor;
IRSensor *leftMiddleIRSensor;
IRSensor *rightMiddleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;
 
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotActions *robotActions;
WorldState *worldState;
// RobotState *robotState;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
}