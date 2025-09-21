#include <Arduino.h>
#include "world_state.hpp"
#include <sensor.hpp>

const int left = 2;
const int middle = 3;
const int right = 4;

const int right_PWM = 6;
const int right_DIR = 5;
const int left_PWM = 8;
const int left_DIR = 7;

const int LEFT_LINE = 23;
const int RIGHT_LINE = 22;
const int START_PIN = 0;

int motors[2] = {5, 5};
int ir_sensors[3];
int line_sensors[2];

world_state* ws = new world_state(line_sensors, ir_sensors);

// Sensor* leftIR;
// Sensor* middleIR;
// Sensor* rightIR;

void pullSensors();
void updateState();
void writeMotors();
void debug();

void setup() {
  // put your setup code here, to run once:
  // leftIR = new Sensor();
  // middleIR = new Sensor();
  // rightIR = new Sensor();

  pinMode(left, INPUT);
  pinMode(middle, INPUT);
  pinMode(right, INPUT);

  pinMode(right_PWM, OUTPUT);
  pinMode(right_DIR, OUTPUT);
  pinMode(left_DIR, OUTPUT);
  pinMode(left_PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  pullSensors();
  debug();
  writeMotors();
  ws->clean_sensors();
  debug();
}

void pullSensors() {
  ir_sensors[0] = digitalRead(left);
  ir_sensors[1] = digitalRead(middle);
  ir_sensors[2] = digitalRead(right);
}

void debug() {
  Serial.print(ir_sensors[0]);
  Serial.print(ir_sensors[1]);
  Serial.print(ir_sensors[2]);
  Serial.println();
}

void writeMotors() {
  digitalWrite(left_DIR, (motors[0] > 0));
  analogWrite(left_PWM, abs(motors[0]));
  digitalWrite(right_DIR, (motors[1] > 0));
  analogWrite(right_PWM, abs(motors[1]));
}