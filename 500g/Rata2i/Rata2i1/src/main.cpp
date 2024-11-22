#include <Arduino.h>

#include "robotAction.h"
#include "motorDriver.h"
#include "IRSensor.h"
#include "lineReader.h"
#include "Accelerometer.h"

const int RIGHT_PWM = -1;
const int RIGHT_DIR = -1;
const int LEFT_PWM = -1;
const int LEFT_DIR = -1;
const int LEFT_FRONT_IR = -1;
const int RIGHT_FRONT_IR = -1;
const int LEFT_BACK_IR = -1;
const int RIGHT_BACK_IR = -1;
const int LINE_SENSOR_LEFT = -1;
const int LINE_SENSOR_RIGHT = -1;
const int START_PIN = -1;

IRSensor *leftFrontIR;
IRSensor *rightFrontIR;
IRSensor *leftBackIR;
IRSensor *rightBackIR;
lineReader *lineSensorLeft;
lineReader *lineSensorRight;

motorDriver *leftMotorDriver;
motorDriver *rightMotorDriver;
robotAction *robot;

void setup() {
  Serial.begin(9600);

  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);

  pinMode(LEFT_FRONT_IR, INPUT);
  pinMode(RIGHT_FRONT_IR, INPUT);
  pinMode(LEFT_BACK_IR, INPUT);
  pinMode(RIGHT_BACK_IR, INPUT);
  pinMode(LINE_SENSOR_LEFT, INPUT);
  pinMode(LINE_SENSOR_RIGHT, INPUT);
  pinMode(START_PIN, INPUT);

  leftMotorDriver = new motorDriver();
  rightMotorDriver = new motorDriver();
  robot = new robotAction();
  rightFrontIR = new IRSensor();
  leftFrontIR = new IRSensor();
  rightBackIR = new IRSensor();
  leftBackIR = new IRSensor();
  lineSensorLeft = new lineReader();
  lineSensorRight = new lineReader();
  
  
}

void loop() {
  
}

int myFunction(int x, int y) {
  return x + y;
}