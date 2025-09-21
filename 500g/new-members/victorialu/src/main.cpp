#include <Arduino.h>
#include <world_state.hpp>
#include <robot_actions.hpp>
#include <algorithms.hpp>

const int leftSensor = 2;
const int middleSensor = 3;
const int rightSensor = 4;

const int rightPWM = 6;
const int rightDIR = 5;
const int leftPWM = 8;
const int leftDIR = 7;

const int LEFT_LINE = 23;
const int RIGHT_LINE = 22;

const int START_PIN = 0;

int motors[2] = {255, 255};
int line_sensors[2] = {32, 790};
int ir_sensors[3] = {1, 1, 1};

world_state state(ir_sensors, line_sensors);

void pullSensors();
void updateMotors();
void updateState();
void debug();

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(rightPWM, OUTPUT);
  pinMode(rightDIR, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);

  pinMode(START_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Setup complete");

  while (digitalRead(START_PIN) == 0) {
    Serial.println("Waiting");
  }
}

void loop() {
  if (digitalRead(START_PIN) == 1) {
    pullSensors();
    updateMotors();
    debug();
  } else {
    motors[0] = 0;
    motors[1] = 0;
    updateMotors();
  }
  
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSensor);
  ir_sensors[1] = digitalRead(middleSensor);
  ir_sensors[2] = digitalRead(rightSensor);

  line_sensors[0] = analogRead(LEFT_LINE);
  line_sensors[1] = analogRead(RIGHT_LINE);
}

void updateMotors() {
  if (motors[0] > 0 && motors[1] > 0) {
    //forward
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, motors[0]);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, motors[1]);
  } else if (motors[0] < 0 && motors[1] < 0) {
    //backward
    digitalWrite(leftDIR, LOW);
    analogWrite(leftPWM, -motors[0]);
    digitalWrite(rightDIR, LOW);
    analogWrite(rightPWM, -motors[1]);
  } else if (motors[0] > 0 && motors[1] < 0) {
    //turn right
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, motors[0]);
    digitalWrite(rightDIR, LOW);
    analogWrite(rightPWM, -motors[1]);
  } else if (motors[0] < 0 && motors[1] > 0) {
    //turn left
    digitalWrite(leftDIR, LOW);
    analogWrite(leftPWM, -motors[0]);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, motors[1]);
  } else {
    //brake
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, 255);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, 255);
  }
  
}

void updateState() {
  
}

void debug() {
  int i = 0;
  i ++;
  if (i % 100 == 0) {
    Serial.print("IR: ");
    Serial.print(ir_sensors[0]);
    Serial.print(" ");
    Serial.print(ir_sensors[1]);
    Serial.print(" ");
    Serial.print(ir_sensors[2]);

    Serial.print(" | Line: ");
    Serial.print(line_sensors[0]);
    Serial.print(" ");
    Serial.println(line_sensors[1]);

    Serial.print(" | Motors: ");
    Serial.print(motors[0]);
    Serial.print(" ");
    Serial.println(motors[1]);
  }
}