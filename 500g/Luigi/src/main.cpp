#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"

const int leftSensor = 2;
const int middleSensor = 3;
const int rightSensor = 4;

const int rightB = 6;
const int rightF = 5;
const int leftB = 8;
const int leftF = 7;

const int startPin = 0;

long currentMillis = 0;
int printCounter = 0;

float* avgs;
int motors[2] = {0};
int sensors[3] = {0};

world_state* ws = new world_state(sensors);
timer* motor_timer = new timer(&currentMillis);
motor_actions* ma = new motor_actions(motors, sensors, motor_timer);


void drive();
void pullSensors();
void writeMotors();
void debug();

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(startPin, INPUT);

  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);

  Serial.begin(9600);
  // while (digitalRead(startPin) == 0) {
  //   printCounter++;
  //   if (printCounter%100000 == 0)
  //     Serial.println("Waiting to start");
  // }
}

void loop() {
  // while (digitalRead(startPin) == 0) {
  //   printCounter++;
  //   if (printCounter%100000 == 0)
  //     Serial.println("Waiting to start");
  // }
  pullSensors();
  ws->clean_sensors();
  avgs = ws->get_sensors_avg();
  // debug();
  ma->drive_avgs(avgs);
  writeMotors();
}

void pullSensors() {
  sensors[0] = digitalRead(leftSensor);
  sensors[1] = digitalRead(middleSensor);
  sensors[2] = digitalRead(rightSensor);
  currentMillis = millis();

}

void debug() {
  printCounter++;
  if (printCounter % 10000 == 0) {
    Serial.print(sensors[0]);
    Serial.print(sensors[1]);
    Serial.print(sensors[2]);
    Serial.println();
  }
}

void writeMotors() {
  if (motors[0] > 0) {
    analogWrite(leftF, abs(motors[0]));
    analogWrite(leftB, 0);
  }
  else if (motors[0] < 0) {
    analogWrite(leftB, abs(motors[0]));
    analogWrite(leftF, 0);
  }
  else {
    analogWrite(leftF, 255);
    analogWrite(leftB, 255);
  }
  if (motors[1] > 0) {
    analogWrite(rightF, abs(motors[1]));
    analogWrite(rightB, 0);
  }
  else if (motors[1] < 0) {
    analogWrite(rightB, abs(motors[1]));
    analogWrite(rightF, 0);
  }
  else {
    analogWrite(rightF, 255);
    analogWrite(rightB, 255);
  }
}