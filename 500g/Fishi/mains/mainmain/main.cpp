#include <Arduino.h>
#include <Wire.h>
#include "sensors/Accelerometer.h"
#include "RobotAction.h"
#include "MotorDriver.h"
#include "WorldState.h"
#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"
#include "RobotState.h"
#include "Timer.h"

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

// placeholder code for IMU (if I can ever get it working) :(

// const double STUPID_GRAVITY_SCALE_FACTOR = 211.0;
// const double MAX_GYRO_DPS = 2000.0;
// constexpr float SD_ACC = 0.1;              // Adjusted standard deviation for acceleration
// constexpr float SD_VEL = 0.1;              // Adjusted standard deviation for velocity
// constexpr float ALPHA = 0.5;               // Gain of heading update

// sensors
Velocity *velocity;
IRSensor *leftIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;

// robot stuff
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotAction *robotAction;
WorldState *worldState;
RobotState *robotState;

//etc
Timer *accelerometerTimer;
Timer *debugTimer;

const bool DEBUGGING = false;

void debug();
void writeMotors();
void pollSensors();
void calculateState(int time);

void setup() {
  Serial.begin(9600);

  // IMU stuff that breaks the program

  // initializing IMU
  // Wire.begin();
  // IMU.begin();
  // IMU.startAccel(100, 16);
  // IMU.startGyro(100, 2000);
  // fusion.setup();

  pinMode(L_MOTOR_IN_1, OUTPUT);
  pinMode(L_MOTOR_IN_2, OUTPUT);
  pinMode(R_MOTOR_IN_1, OUTPUT);
  pinMode(R_MOTOR_IN_2, OUTPUT);

  pinMode(L_IR, INPUT);
  pinMode(M_IR, INPUT);
  pinMode(R_IR, INPUT);
  pinMode(L_LINE, INPUT);
  pinMode(R_LINE, INPUT);
  pinMode(START_MOD, INPUT);
  
  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();
  robotAction = new RobotAction(leftMotorDriver, rightMotorDriver, 40);
  velocity = new Velocity();
  leftIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();
  worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, middleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotAction);
  accelerometerTimer = new Timer();
  debugTimer = new Timer();
  
  accelerometerTimer->setTimeInterval(10);
  debugTimer->setTimeInterval(10000);

  leftLineSensor->setThreshold(800);
  rightLineSensor->setThreshold(800);

  if (!DEBUGGING) {
    while (!digitalRead(START_MOD)) {r
      Serial.print(digitalRead(START_MOD));
      Serial.println(" Waiting for start signal");
    }
  }

  robotState->setStartTimer(millis());
}

void loop() {
  debug();
  pollSensors();
  calculateState(millis());
  writeMotors();
  if (!DEBUGGING) {
    if (!digitalRead(START_MOD)) {
      while(true) {
        robotAction->brake();
        writeMotors();
        Serial.println("braking");
      }
    }
  }
}

void writeMotors() {
  int leftDirection = leftMotorDriver->getDirection();
  int leftSpeed = leftMotorDriver->getSpeed();
  
  if (leftDirection == 0) {  // if direction is forward
     analogWrite(L_MOTOR_IN_1, leftSpeed);
     analogWrite(L_MOTOR_IN_2, 0);
  } else {                    // if direction is back
     analogWrite(L_MOTOR_IN_1, 0);
     analogWrite(L_MOTOR_IN_2, leftSpeed);
  }

  int rightDirection = rightMotorDriver->getDirection();
  int rightSpeed = rightMotorDriver->getSpeed();

  if (rightDirection == 0) {  // if direction is forward
     analogWrite(R_MOTOR_IN_1, rightSpeed);
     analogWrite(R_MOTOR_IN_2, 0);
  } else {                    // if direction is back
     analogWrite(R_MOTOR_IN_1, 0);
     analogWrite(R_MOTOR_IN_2, rightSpeed);
  }
}

void pollSensors() {
  //implement proper velocity measurement D:
  leftIRSensor->setValue(!digitalRead(L_IR));
  middleIRSensor->setValue(!digitalRead(M_IR));
  rightIRSensor->setValue(!digitalRead(R_IR));
  leftLineSensor->setValue(analogRead(L_LINE));
  rightLineSensor->setValue(analogRead(R_LINE));
}

void calculateState(int time) {
  robotState->calculateState(time);
}

void debug() {
  if (true) {
    Serial.print(digitalRead(DIP_1));
    Serial.print(digitalRead(DIP_2));
    Serial.print(" ");
  }

  if (false) {
    Serial.print(leftMotorDriver->getDirection());
    Serial.print(leftMotorDriver->getSpeed());
    Serial.print(" ");
    Serial.print(rightMotorDriver->getDirection());
    Serial.print(rightMotorDriver->getSpeed());
    Serial.print(" ");

  }
  if (false) {
    Serial.print(digitalRead(START_MOD));
    Serial.print(" ");
    Serial.print(leftIRSensor->getValue());
    Serial.print(middleIRSensor->getValue());
    Serial.print(rightIRSensor->getValue());
    Serial.print(" ");
    Serial.print(analogRead(L_LINE));
    Serial.print(" ");
    Serial.print(analogRead(R_LINE));
    Serial.print(" ");
  }
  if (false) {
    Serial.print(velocity->getX()); 
    Serial.print(" ");
    Serial.print(velocity->getY()); // -1000 = forward accel
    Serial.print(" ");
    Serial.print(velocity->getZ()); // up / down
  }
  if (false) {
    Serial.print(rightMotorDriver->getSpeed());
    Serial.print(rightMotorDriver->getDirection());
    Serial.print(leftMotorDriver->getSpeed());
    Serial.print(leftMotorDriver->getDirection());
  }
  if (false) {
    Serial.print(leftLineSensor->getValue());
    // Serial.print(leftLineSensor->getThreshold());
    Serial.print(rightLineSensor->getValue());
    // Serial.print(leftLineSensor->getThreshold());
    Serial.print((int)worldState->getPosition());
  }
  Serial.println();
}