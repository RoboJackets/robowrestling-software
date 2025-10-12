/**
 * Temporarii Main File - Da Four-Wheel Drive
 */
#include <Arduino.h>

/**
 * Imports
 */
#include "Robot/robotActions.hpp"
#include "Robot/motorDriver.hpp"
#include "Sensors/WorldState.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"
#include "Robot/robotState.hpp"
#include "Sensors/Timer.hpp"

/**
 * Pinouts
 */
const int fr_pwm = 9;
const int fr_dir = 10;
const int fl_pwm = 8;
const int fl_dir = 7;
const int br_pwm = 18;
const int br_dir = 13;
const int bl_pwm = 19;
const int bl_dir = 21;

const int left_ir = 22;
const int mid_ir = 15;
const int right_ir = 40;

const int left_line = 14;
const int right_line = 24;

// Start mod
// const int start_mod = 0;

/**
 * Object Definition
 */
IrSensor *leftIR;
IrSensor *midIR;
IrSensor *rightIR;
// Temp sensors: Replace with actual when we get 5
IrSensor *tempIRL;
IrSensor *tempIRR;

LineSensor *leftLine;
LineSensor *rightLine;
// Temp line: Replace with actual when we get 4
LineSensor *tempLineBL;
LineSensor *tempLineBR;

MotorDriver *flMotor;
MotorDriver *frMotor;
MotorDriver *blMotor;
MotorDriver *brMotor;

RobotActions *action;
WorldState *world;
Algorithm *algo;

// Tempi 😃
RobotState *tempi;

Timer *timer;
// if debugging is true it will skip the start module check.
const bool DEBUGGING = true;

// function definitions
void debug();
void writeMotors();
void pollSensors();
void calculateState();

/**
 * Setup Pin Definitions
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Starting Setup");

  // pinmode definitions
  pinMode(fr_pwm, OUTPUT);
  pinMode(fr_dir, OUTPUT);
  pinMode(fl_pwm, OUTPUT);
  pinMode(fl_dir, OUTPUT);

  pinMode(left_ir, INPUT);
  pinMode(mid_ir, INPUT);
  pinMode(right_ir, INPUT);

  pinMode(left_line, INPUT);
  pinMode(right_line, INPUT);

  // pinMode(start_mod, INPUT);

  leftIR = new IrSensor();
  rightIR = new IrSensor();
  midIR = new IrSensor();
  // Replace with actual IR
  tempIRL = new IrSensor();
  tempIRR = new IrSensor();


  leftLine = new LineSensor();
  rightLine = new LineSensor();
  // Replace with actual line
  tempLineBL = new LineSensor();
  tempLineBR = new LineSensor();

  flMotor = new MotorDriver();
  frMotor = new MotorDriver();
  blMotor = new MotorDriver();
  brMotor = new MotorDriver();

  IrSensor *irSensors[5] = {tempIRL, leftIR, midIR, rightIR, tempIRR};
  LineSensor *lineSensors[4] = {tempLineBL, leftLine, rightLine, tempLineBR};

  // Temp settings
  tempLineBL->setValue(1000);
  tempLineBR->setValue(1000);

   // Setting up class structure
  action = new RobotActions(blMotor, flMotor, frMotor, brMotor);
  world = new WorldState(irSensors, lineSensors);
  timer = new Timer(millis());
  algo = new Algorithm(action, timer);

  tempi = new RobotState(world, algo);
  timer->set_action_timer(100);
}

/**
 * Main loop
 */
void loop() {
  // 5 Seconds before start for comp
  // Serial.print("LIR: ");
  // Serial.println(analogRead(left_ir));
  // Serial.print("RIR: ");
  // Serial.println(analogRead(right_ir));
  // Serial.print("MIR: ");
  // Serial.println(analogRead(mid_ir));
  // Serial.println(" ");
  pollSensors();
  calculateState();
  writeMotors();
}

/**
 * Update Sensors
 */
void pollSensors() {
  leftIR->setValue(digitalRead(left_ir));
  midIR->setValue(digitalRead(mid_ir));
  rightIR->setValue(digitalRead(right_ir));

  leftLine->setValue(analogRead(left_line));
  rightLine->setValue(analogRead(right_line));

  // Debug printing
  // Serial.print("Left Line On Line: ");
  // Serial.println(world->getIsOnLine());
  // Serial.print("Left Line: ");
  // Serial.println(leftLine->getValue());

  timer->update_time(millis());
}

/**
 * Calc State using algorithm
 */
void calculateState() {
  tempi->runAlgorithm();
}

/**
 * Write to motors
 */
void writeMotors() {
  // 0: forward, 1: backward
  // analogWrite(fr_pwm, frMotor->getSpeed());
  // digitalWrite(fr_dir, frMotor->getDirection());
  // analogWrite(fl_pwm, flMotor->getSpeed());
  // digitalWrite(fl_dir, flMotor->getDirection());
  // analogWrite(br_pwm, brMotor->getSpeed());
  // digitalWrite(br_dir, brMotor->getDirection());
  // analogWrite(bl_pwm, blMotor->getSpeed());
  // digitalWrite(bl_dir, blMotor->getDirection());
  analogWrite(fr_pwm, 50);
  digitalWrite(fr_dir, 0);
  analogWrite(fl_pwm, 50);
  digitalWrite(fl_dir, 0);
  analogWrite(br_pwm, 50);
  digitalWrite(br_dir, 0);
  analogWrite(bl_pwm, 150);
  digitalWrite(bl_dir, 1);
  
}

/**
 * Debuggin'
 */
void debug() {
  // if (true) {
  //   Serial.print(digitalRead(START_PIN));
  //   Serial.print(" ");
  //   Serial.print(leftIRSensor->getValue());
  //   Serial.print(middleIRSensor->getValue());
  //   Serial.print(rightIRSensor->getValue());
  //   Serial.print(" ");
  //   Serial.print(analogRead(LEFT_LINE));
  //   Serial.print(" ");
  //   Serial.print(analogRead(RIGHT_LINE));
  //   Serial.print(" ");
  // }
  // if (true)
  // {
  //   Serial.print(rightMotorDriver->getSpeed());
  //   Serial.print(rightMotorDriver->getDirection());
  //   Serial.print(leftMotorDriver->getSpeed());
  //   Serial.print(leftMotorDriver->getDirection());
  // }
  // Serial.println();
}