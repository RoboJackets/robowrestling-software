#include <Arduino.h>

// Defining Pins
// #define name value
//OUTPUT Pins
#define LEFT_MOTOR_PIN A1
#define RIGHT_MOTOR_PIN A2

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
bool shifting = false;
// put your setup code here, to run once:
void setup() {
  //Defines whether a pin is input or output
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(TOP_LEFT_LINE_PIN, INPUT);
  pinMode(TOP_RIGHT_LINE_PIN, INPUT);
  pinMode(BACK_LEFT_LINE_PIN, INPUT);
  pinMode(BACK_RIGHT_LINE_PIN, INPUT);
  pinMode(MID_IR_PIN, INPUT);
  pinMode(MIDLEFT_IR_PIN, INPUT);
  pinMode(MIDRIGHT_IR_PIN, INPUT);
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);
}
// put your main code here, to run repeatedly:
void loop() {
  if (digitalRead(MID_IR_PIN) == 1) {
    //Set robot to full power (100)
    analogWrite(LEFT_MOTOR_PIN, 100);
    analogWrite(RIGHT_MOTOR_PIN, 100);
  } else {
    if (shifting) {
      analogWrite(LEFT_MOTOR_PIN, 50);
      analogWrite(RIGHT_MOTOR_PIN, 80);
      shifting = false;
    } else {
      analogWrite(LEFT_MOTOR_PIN, 80);
      analogWrite(RIGHT_MOTOR_PIN, 50);
      shifting = true;
    }
  }
}