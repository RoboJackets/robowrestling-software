#include <Arduino.h>
#include <Wire.h>
#include <accIntegral.h>

#include "ICM42670P.h"
#include "sensors/Accelerometer.h"
#include "RobotAction.h"
#include "MotorDriver.h"
#include "WorldState.h"
#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"
#include "RobotState.h"
#include "utility/Timer.h"

const int RIGHT_PWM = 6;
const int RIGHT_DIR = 5;
const int LEFT_PWM = 8;
const int LEFT_DIR = 7;
const int LEFT_IR = 2;
const int MIDDLE_IR = 3;
const int RIGHT_IR = 4;
const int LEFT_LINE = A8;
const int RIGHT_LINE = A9;
const int START_PIN = 34;

// placeholder code for IMU (if I can ever get it working) :(

// const double STUPID_GRAVITY_SCALE_FACTOR = 211.0;
// const double MAX_GYRO_DPS = 2000.0;
// constexpr float SD_ACC = 0.1;              // Adjusted standard deviation for acceleration
// constexpr float SD_VEL = 0.1;              // Adjusted standard deviation for velocity
// constexpr float ALPHA = 0.5;               // Gain of heading update

// sensors
ICM42670 IMU(Wire, 1);
accIntegral fusion;

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

  leftLineSensor->setThreshold(200);
  rightLineSensor->setThreshold(200);

  if (!DEBUGGING) {
    while (!digitalRead(START_PIN)) {
      Serial.print(digitalRead(START_PIN));
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
    if (!digitalRead(START_PIN)) {
      while(true) {
        robotAction->brake();
        Serial.println("braking");
      }
    }
  }
}

void writeMotors() {
  analogWrite(RIGHT_PWM, rightMotorDriver->getSpeed());
  digitalWrite(RIGHT_DIR, rightMotorDriver->getDirection());
  analogWrite(LEFT_PWM, leftMotorDriver->getSpeed());
  digitalWrite(LEFT_DIR, leftMotorDriver->getDirection());
}

void pollSensors() {
  //implement proper velocity measurement D:
  leftIRSensor->setValue(digitalRead(LEFT_IR));
  middleIRSensor->setValue(digitalRead(MIDDLE_IR));
  rightIRSensor->setValue(digitalRead(RIGHT_IR));
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
}

void calculateState(int time) {
  robotState->calculateState(time);
}

void debug() {
  if (false) {
    Serial.print(leftMotorDriver->getDirection());
    Serial.print(leftMotorDriver->getSpeed());
    Serial.print(" ");
    Serial.print(rightMotorDriver->getDirection());
    Serial.print(rightMotorDriver->getSpeed());
    Serial.print(" ");

  }
  if (true) {
    Serial.print(digitalRead(START_PIN));
    Serial.print(" ");
    Serial.print(leftIRSensor->getValue());
    Serial.print(middleIRSensor->getValue());
    Serial.print(rightIRSensor->getValue());
    Serial.print(" ");
    Serial.print(analogRead(LEFT_LINE));
    Serial.print(" ");
    Serial.print(analogRead(RIGHT_LINE));
    Serial.print(" ");
  }
  if (false) {
    Serial.print(velocity->getX()); 
    Serial.print(" ");
    Serial.print(velocity->getY()); // -1000 = forward accel
    Serial.print(" ");
    Serial.print(velocity->getZ()); // up / down
  }
  if (true) {
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