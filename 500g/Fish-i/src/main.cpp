#include <Arduino.h>

const int START_PIN = 12;
const int RIGHT_IN1 = 9;
const int RIGHT_IN2 = 10;
const int LEFT_IN1 = 5;
const int LEFT_IN2 = 6;
const int LEFT_IR = 2;
const int MIDDLE_IR = 3;
const int RIGHT_IR = 4;
const int LEFT_LINE = A0;
const int RIGHT_LINE = A1;
const int DIP_1 = 7;
const int DIP_2 = 8;

const int MAX_SPEED = 255;
const int MODERATE_SPEED = 210;

int left_threshold = 500;
int right_threshold = 500;

void forward();
void backward();
void brake();
void spinLeft();
void spinRight();
void turnLeft();
void turnRight();

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);

  pinMode(START_PIN, INPUT);
  pinMode(LEFT_IR, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_LINE, INPUT);
  pinMode(RIGHT_LINE, INPUT);
  pinMode(DIP_1, INPUT);
  pinMode(DIP_2, INPUT);
  // while (!digitalRead(START_PIN)) {
  //   Serial.print(digitalRead(START_PIN));
  //   Serial.println(" Waiting for start signal");
  //   // calibrateLineSensors();
  // }
  unsigned long starttime = millis();
  bool calibrated_flag = false;
  while ((millis() - starttime) <= 5000) {
    if (!calibrated_flag) {
      left_threshold = (analogRead(LEFT_LINE) - 100);
      right_threshold = (analogRead(RIGHT_LINE) - 100);
    }
    Serial.print("Starting in: ");
    Serial.print(5000 - (millis() - starttime));
    Serial.print(" | Thresholds set to: ");
    Serial.print(left_threshold);
    Serial.print(" ");
    Serial.println(right_threshold);
  }
}

void loop() {
  bool online = (analogRead(LEFT_LINE) < left_threshold || analogRead(RIGHT_LINE) < right_threshold);
  if (online) {
    while (online) {
      online = (analogRead(LEFT_LINE) < left_threshold || analogRead(RIGHT_LINE) < right_threshold);
      Serial.println("backing up");
      backward();
    }
    delay(500);
    Serial.println("spinning");
    spinLeft();
    delay(300);
  } else {
    if (digitalRead(MIDDLE_IR)) {
      forward();
      Serial.println("forward");
    } else if (digitalRead(LEFT_IR)) {
      Serial.println("left");
      turnLeft();
    } else if (digitalRead(RIGHT_IR)) {
      Serial.println("right");
      turnRight();
    } else {
      forward();
      Serial.println("forward");
    }
  }
  if (!digitalRead(START_PIN)) {
    while(true) {
      brake();
      Serial.println("braking");
    }
  }
}

void forward() {
  analogWrite(LEFT_IN1, MAX_SPEED);
  analogWrite(LEFT_IN2, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(RIGHT_IN2, MAX_SPEED);
}

void backward() {
  analogWrite(LEFT_IN1, 0);
  analogWrite(LEFT_IN2, MAX_SPEED);
  analogWrite(RIGHT_IN1, MAX_SPEED);
  analogWrite(RIGHT_IN2, 0);
}

void brake() {
  analogWrite(LEFT_IN1, MAX_SPEED);
  analogWrite(LEFT_IN2, MAX_SPEED);
  analogWrite(RIGHT_IN1, MAX_SPEED);
  analogWrite(RIGHT_IN2, MAX_SPEED);
}

void spinLeft() {
  analogWrite(LEFT_IN1, 0);
  analogWrite(LEFT_IN2, MAX_SPEED);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(RIGHT_IN2, MAX_SPEED);
}

void spinRight() {
  analogWrite(LEFT_IN1, MAX_SPEED);
  analogWrite(LEFT_IN2, 0);
  analogWrite(RIGHT_IN1, MAX_SPEED);
  analogWrite(RIGHT_IN2, 0);
}

void turnLeft() {
  analogWrite(LEFT_IN1, MODERATE_SPEED);
  analogWrite(LEFT_IN2, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(RIGHT_IN2, MAX_SPEED);
}

void turnRight() {
  analogWrite(LEFT_IN1, MAX_SPEED);
  analogWrite(LEFT_IN2, 0);
  analogWrite(RIGHT_IN1, 0);
  analogWrite(RIGHT_IN2, MODERATE_SPEED);
}