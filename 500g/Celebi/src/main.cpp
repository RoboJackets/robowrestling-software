#include <Arduino.h>

const int RIGHT_PWM = 6;
const int RIGHT_DIR = 5;
const int LEFT_PWM = 8;
const int LEFT_DIR = 7;
const int LEFT_IR = 2;
const int MIDDLE_IR = 3;
const int RIGHT_IR = 4;
const int LEFT_LINE = A6;
const int RIGHT_LINE = A7;
const int START_PIN = 34;

int left = 0;
int right = 0;
int middle = 0;
int tol_p = 50;
int tol_m = -50;
void debug();

void setup() {

  Serial.begin(9600);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);

  pinMode(LEFT_IR, INPUT);
  pinMode(MIDDLE_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_LINE, INPUT);
  pinMode(RIGHT_LINE, INPUT);
  pinMode(START_PIN, INPUT);
}

void loop() {
  left += 2*digitalRead(LEFT_IR);
  right += 2*digitalRead(RIGHT_IR);
  middle += 2*digitalRead(MIDDLE_IR);
  left--;
  right--;
  middle--;
  left = left < tol_m ? tol_m : left;
  left = left > tol_p ? tol_p : left;
  
  middle = middle < tol_m ? tol_m : middle;
  middle = middle > tol_p ? tol_p : middle;

  right = right < tol_m ? tol_m : right;
  right = right > tol_p ? tol_p : right;
  debug();
}

void debug() {
  Serial.print(left > 0);
  Serial.print(" ");
  Serial.print(right > 0);
  Serial.print(" ");
  Serial.print(middle > 0);
  //Serial.print(" ");
  //Serial.print(analogRead(LEFT_LINE));
  //Serial.print(" ");
  //Serial.print(analogRead(RIGHT_LINE));
  Serial.println();
}