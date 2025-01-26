#include <Arduino.h>
#include "Sensors/WorldState.h"
#include "Robot/robotActions.hpp"

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

IrSensor *irSensor;
LineSensor *lineSensor;
WorldState world;

RobotActions action;

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
  irSensor = new IrSensor[5];
  lineSensor = new LineSensor[4];
  // World State
  world = WorldState(irSensor, lineSensor);
  // Robot Actions
  //action = RobotActions();
}
// put your main code here, to run repeatedly:
void loop() {
  pollSensors();
  calcState();
  writeMotors();
}

void pollSensors() {
  lineSensor[0].setValue(analogRead(TOP_LEFT_LINE_PIN));
  lineSensor[1].setValue(analogRead(BACK_LEFT_LINE_PIN));
  lineSensor[2].setValue(analogRead(TOP_RIGHT_LINE_PIN));
  lineSensor[3].setValue(analogRead(BACK_RIGHT_LINE_PIN));

  irSensor[0].setValue(digitalRead(LEFT_IR_PIN));
  irSensor[1].setValue(digitalRead(MIDLEFT_IR_PIN));
  irSensor[2].setValue(digitalRead(MID_IR_PIN));
  irSensor[3].setValue(digitalRead(MIDRIGHT_IR_PIN));
  irSensor[4].setValue(digitalRead(RIGHT_IR_PIN));
}
void calcState() {
  // Calculate States
}
void writeMotors() {
  // Write to Motors digitalWrite()
  digitalWrite(LEFT_FRONT_MOTOR_PIN, 0);

}