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
const int fr_move_forward = 7;
const int fr_move_backward = 8;
const int fl_move_forward = 9;
const int fl_move_backward = 10;
const int br_move_forward = 11;
const int br_move_backward = 12;
const int bl_move_forward = 24;
const int bl_move_backward = 25;

const int left_ir = 30;
const int mid_ir = 24;
const int right_ir = 2;

const int left_line = 22;
const int fr_line = 15;

// Start mod
// const int start_mod = 21;

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

// Prints debugging every few times to avoid spam
int debug_counter = 0;

// function definitions
void debug();
void writeMotors();
void pollSensors();
void calculateState();

/**
 * Setup Pin Definitions
 */
void setup() {
  // pinmode definitions
  pinMode(fr_move_forward, OUTPUT);
  pinMode(fr_move_backward, OUTPUT);
  pinMode(fl_move_forward, OUTPUT);
  pinMode(fl_move_backward, OUTPUT);
  pinMode(br_move_forward, OUTPUT);
  pinMode(br_move_backward, OUTPUT);
  pinMode(bl_move_forward, OUTPUT);
  pinMode(bl_move_backward, OUTPUT);

  pinMode(left_ir, INPUT);
  pinMode(mid_ir, INPUT);
  pinMode(right_ir, INPUT);

  // pinMode(left_line, INPUT);
  // pinMode(right_line, INPUT);
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

  timer = new Timer(millis());

  Serial.println("Starting Setup");
  Serial.begin(9600);
}

/**
 * Main loop
 */
void loop() {
  // 5 Seconds before start for comp
  pollSensors();
  // calculateState();
  // writeMotors();
  // debug_counter++;
  // if (debug_counter >= 20) {
  //   debug();
  //   debug_counter = 0;
  // }
}

/**
 * Update Sensors
 */
void pollSensors() {
  leftIR->setValue(digitalRead(left_ir));
  midIR->setValue(digitalRead(mid_ir));
  rightIR->setValue(digitalRead(right_ir));

  // leftLine->setValue(analogRead(left_line));
  rightLine->setValue(analogRead(fr_line));

  Serial.print("FR Line: ");
  Serial.println(analogRead(fr_line));
  // Serial.print("Right IR: ");
  // Serial.println(rightIR->getValue());

  timer->updateTime();
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
  brMotor->setSpeed(100);
  brMotor->setDirection(0);

  analogWrite(br_move_forward, 255);
  analogWrite(br_move_backward, 0);
  // analogWrite(fl_move_forward, flMotor->getDirection() == 0 ? flMotor->getSpeed() : 0);
  // analogWrite(fl_move_backward, flMotor->getDirection() == 1 ? flMotor->getSpeed() : 0);
  // analogWrite(br_move_forward, brMotor->getDirection() == 0 ? brMotor->getSpeed() : 0);
  // analogWrite(br_move_backward, brMotor->getDirection() == 1 ? brMotor->getSpeed() : 0);
  // analogWrite(bl_move_forward, blMotor->getDirection() == 0 ? blMotor->getSpeed() : 0);
  // analogWrite(bl_move_backward, blMotor->getDirection() == 1 ? blMotor->getSpeed() : 0);
}

/**
 * Debuggin'
 */
void debug() {
  Serial.println("Debug loop: ");
  // IR Sensors
  Serial.print("Left IR: ");
  Serial.println(leftIR->getValue());
  Serial.print("Mid IR: ");
  Serial.println(midIR->getValue());
  Serial.print("Right IR: ");
  Serial.println(rightIR->getValue());

  // Line Sensors
  Serial.print("Left Line: ");
  Serial.println(leftLine->getValue());
  Serial.print("Right Line: ");
  Serial.println(rightLine->getValue());
  
  // Motor States
  Serial.print("FL Motor: ");
  Serial.print(flMotor->getSpeed());
  Serial.print("FR Motor: ");
  Serial.println(frMotor->getSpeed());
  Serial.print("BL Motor: ");
  Serial.print(blMotor->getSpeed());
  Serial.print("BR Motor: ");
  Serial.println(brMotor->getSpeed());
}