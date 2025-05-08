#include <Arduino.h>

const int L_IR = 2;
const int M_IR = 3;
const int R_IR = 4;
const int L_LINE = A0;
const int R_LINE = A1;
const int START_MOD = 12;
const int L_MOTOR_IN_1 = 5;
const int L_MOTOR_IN_2 = 6;
const int R_MOTOR_IN_1 = 9;
const int R_MOTOR_IN_2 = 10;
const int DIP_1 = 7;
const int DIP_2 = 8;

void forward(int speed);
void backward(int speed);
void brake();

void setup() {
  pinMode(L_MOTOR_IN_1, OUTPUT);
  pinMode(L_MOTOR_IN_2, OUTPUT);
  pinMode(R_MOTOR_IN_1, OUTPUT);
  pinMode(R_MOTOR_IN_2, OUTPUT);
}

void loop() {
  forward(255);
  delay(1000);
  brake();
  delay(500);
  backward(255);
  delay(1000);
  brake();
  delay(500);
}

void forward(int speed) {
  analogWrite(L_MOTOR_IN_1, speed);
  analogWrite(L_MOTOR_IN_2, 0);
  analogWrite(R_MOTOR_IN_1, speed);
  analogWrite(R_MOTOR_IN_2, 0);
}

void backward(int speed) {
  analogWrite(L_MOTOR_IN_1, 0);
  analogWrite(L_MOTOR_IN_2, speed);
  analogWrite(R_MOTOR_IN_1, 0);
  analogWrite(R_MOTOR_IN_2, speed);
}

void brake() {
  analogWrite(L_MOTOR_IN_1, 0);
  analogWrite(L_MOTOR_IN_2, 0);
  analogWrite(R_MOTOR_IN_1, 0);
  analogWrite(R_MOTOR_IN_2, 0);
}