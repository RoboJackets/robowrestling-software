#include <Arduino.h>

#define START_MOD 6

#define B_PWM 8
#define B_IN1 10
#define B_IN2 12
#define A_PWM 7
#define A_IN1 9
#define A_IN2 11

#define L_30 34
#define L_60 35
#define L_90 36
#define R_30 30
#define R_60 29
#define R_90 28
#define Center 33

#define TL A16
#define TR A12

int motor_speed = 0;

void forward(int speed);
void left(int speed);
void right(int speed);
void brake();

void setup() {
  Serial.begin(9600);
  pinMode(B_PWM, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);

  pinMode(L_30, INPUT_PULLDOWN);
  pinMode(L_60, INPUT_PULLDOWN);
  pinMode(L_90, INPUT_PULLDOWN);
  pinMode(R_30, INPUT_PULLDOWN);
  pinMode(R_60, INPUT_PULLDOWN);
  pinMode(R_90, INPUT_PULLDOWN);
  pinMode(Center, INPUT_PULLDOWN);

  while (!digitalRead(START_MOD)) {
    Serial.print(millis());
    Serial.print(": ");
    Serial.print(digitalRead(START_MOD));
    Serial.println(" Waiting for start signal");
  }
}

void loop() {
  bool is_left = digitalRead(L_60) || digitalRead(L_90);
  bool is_right = digitalRead(R_60) || digitalRead(R_90);
  bool is_center = digitalRead(Center); 
  if (is_center) {
    forward(160);
  }
  else if (is_left) {
    left(127);
  }
  else if (is_right) {
    right(127);
  }
  else {
    brake();
  }
  if (!digitalRead(START_MOD)) {
    while(true) {
      brake();
      Serial.print(millis());
      Serial.println(": braking");
    }
  }
}

void forward(int speed) {
  digitalWrite(A_IN1, 0);
  digitalWrite(A_IN2, 1);
  digitalWrite(B_IN1, 0);
  digitalWrite(B_IN2, 1);
  analogWrite(A_PWM, speed);
  analogWrite(B_PWM, speed);
}

void left(int speed) {
  digitalWrite(A_IN1, 1);
  digitalWrite(A_IN2, 0);
  digitalWrite(B_IN1, 0);
  digitalWrite(B_IN2, 1);
  analogWrite(A_PWM, speed);
  analogWrite(B_PWM, speed);
}

void right(int speed) {
  digitalWrite(A_IN1, 0);
  digitalWrite(A_IN2, 1);
  digitalWrite(B_IN1, 1);
  digitalWrite(B_IN2, 0);
  analogWrite(A_PWM, speed);
  analogWrite(B_PWM, speed);
}

void brake() {
  digitalWrite(A_IN1, 0);
  digitalWrite(A_IN2, 0);
  digitalWrite(B_IN1, 0);
  digitalWrite(B_IN2, 0);
}