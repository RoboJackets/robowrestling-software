#include <Arduino.h>
#include "Sensors/WorldState.h"

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
// put your setup code here, to run once:
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
  // IrSensor Arrays
  WorldState world = WorldState();
}
// put your main code here, to run repeatedly:
void loop() {
  pollSensors();
  calcState();
  writeMotors();
}

void pollSensors() {
  analogRead(TOP_LEFT_LINE_PIN);
  analogRead(TOP_RIGHT_LINE_PIN);
  analogRead(BACK_LEFT_LINE_PIN);
  analogRead(BACK_RIGHT_LINE_PIN);
  digitalRead(MID_IR_PIN);
  digitalRead(MIDLEFT_IR_PIN);
  digitalRead(MIDRIGHT_IR_PIN);
  digitalRead(LEFT_IR_PIN);
  digitalRead(RIGHT_IR_PIN);
}
void calcState() {
  // Calculate States
}
void writeMotors() {
  // Write to Motors digitalWrite()
}