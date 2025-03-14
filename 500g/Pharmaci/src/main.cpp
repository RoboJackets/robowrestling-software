#include <Arduino.h>
#include <IRSensor.h>
#include <LineSensor.h>
#include <MotorDriver.h>
#include <RobotActions.h>
#include <WorldState.h>
#include <RobotState.h>

IRSensor *leftIRSensor;
IRSensor *leftMiddleIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightMiddleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;
 
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotActions *robotActions;
WorldState *worldState;
RobotState *robotState;

// Shorti Pins
const int RIGHT_PWM = 5;
const int RIGHT_POS = 11;
const int RIGHT_NEG = 13;
const int LEFT_PWM = 3;
const int LEFT_POS = 5;
const int LEFT_NEG = A5;

const int START_MODULE = 10;
const int DIP_SWITCH_1 = A6;
const int DIP_SWITCH_2 = A7;

const int LEFT_IR = 2;
// const int MIDDLE_IR = 3;
// const int RIGHT_IR = 4;
// const int LEFT_LINE = A8;
// const int RIGHT_LINE = A9;
// const int START_PIN = 34;

void setup() {
  Serial.begin(9600);

  pinMode(RIGHT_POS, OUTPUT);
  pinMode(RIGHT_NEG, OUTPUT);
  pinMode(LEFT_POS, OUTPUT);
  pinMode(LEFT_NEG, OUTPUT);

  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);

  pinMode(START_MODULE, INPUT);
  pinMode(DIP_SWITCH_1, INPUT);
  pinMode(DIP_SWITCH_2, INPUT);

  pinMode(LEFT_IR, INPUT);

  leftIRSensor = new IRSensor();

  // leftMotorDriver = new MotorDriver();
  // rightMotorDriver = new MotorDriver();
  // robotActions = new RobotActions(leftMotorDriver, rightMotorDriver);
  // leftIRSensor = new IRSensor();
  // leftMiddleIRSensor = new IRSensor();
  // middleIRSensor = new IRSensor();
  // rightMiddleIRSensor = new IRSensor();
  // rightIRSensor = new IRSensor();
  // leftLineSensor = new LineSensor();
  // rightLineSensor = new LineSensor();

  // worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, leftMiddleIRSensor, middleIRSensor, rightMiddleIRSensor, rightIRSensor);
  // robotState = new RobotState(worldState, robotActions);

}

void loop() {
  int speed = 100;
  int direction = 1;
  
  digitalWrite(RIGHT_POS, 0);
  digitalWrite(RIGHT_NEG, 255);
  digitalWrite(LEFT_POS, 0);
  digitalWrite(LEFT_NEG, 255);


  if (digitalRead(LEFT_IR) == HIGH) {
      analogWrite(RIGHT_PWM, speed);
      analogWrite(LEFT_PWM, speed);
  } else {
      analogWrite(RIGHT_PWM, 0);
      analogWrite(LEFT_PWM, 0);
  }


}


void writeMotors() {
  // analogWrite(RIGHT_PWM, rightMotorDriver->getSpeed());
  // digitalWrite(RIGHT_DIR, rightMotorDriver->getDirection());
  // analogWrite(LEFT_PWM, leftMotorDriver->getSpeed());
  // digitalWrite(LEFT_DIR, leftMotorDriver->getDirection());
}

void calculateState() {
  robotState->calculateState();
}