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
const int fl_move_forward = 10;
const int fl_move_backward = 9;
const int br_move_forward = 12;
const int br_move_backward = 11;
const int bl_move_forward = 25;
const int bl_move_backward = 24;

const int left_ir = 32;
const int fl_ir = 30;
const int mid_ir = 6;
const int fr_ir = 2;
const int right_ir = 1;

const int fl_line = 15;
const int fr_line = 14;
const int bl_line = 16;
const int br_line = 17;

// Start mod
const int start_mod = 33;
bool started = false;
bool end = false;

/**
 * Object Definition
 */
IrSensor *leftIR;
IrSensor *flIR;
IrSensor *midIR;
IrSensor *frIR;
IrSensor *rightIR;

LineSensor *flLine;
LineSensor *frLine;
LineSensor *blLine;
LineSensor *brLine;

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
  pinMode(fl_ir, INPUT);
  pinMode(mid_ir, INPUT);
  pinMode(fr_ir, INPUT);
  pinMode(right_ir, INPUT);

  pinMode(fl_line, INPUT);
  pinMode(fr_line, INPUT);
  pinMode(bl_line, INPUT);
  pinMode(br_line, INPUT);
  pinMode(start_mod, INPUT);

  flIR = new IrSensor();
  frIR = new IrSensor();
  midIR = new IrSensor();
  // Replace with actual IR
  leftIR = new IrSensor();
  rightIR = new IrSensor();


  flLine = new LineSensor();
  frLine = new LineSensor();
  blLine = new LineSensor();
  brLine = new LineSensor();

  flMotor = new MotorDriver();
  frMotor = new MotorDriver();
  blMotor = new MotorDriver();
  brMotor = new MotorDriver();

  IrSensor *irSensors[5] = {leftIR, flIR, midIR, frIR, rightIR};
  LineSensor *lineSensors[4] = {blLine, flLine, frLine, brLine};

   // Setting up class structure
  action = new RobotActions(blMotor, flMotor, frMotor, brMotor);
  world = new WorldState(irSensors, lineSensors);
  timer = new Timer(millis());
  algo = new Algorithm(action, timer);
  tempi = new RobotState(world, algo);

  Serial.println("Starting Setup");
  Serial.begin(9600);

  // while(digitalRead(start_mod) == 0) {
  //   Serial.println("Waiting for signal");
  // }
  // delay(4800);
}

/**
 * Main loop
 */
void loop() {
  // 5 Seconds before start for comp
    // Start Mod
    // if (end == true) {
    //   pollSensors();
    //   calculateState();
    //   writeMotors();
    // }
    
    // if (digitalRead(start_mod) == 1) {
    //   end = true;
    // }

    // Debug
    // debug_counter++;
    // if (debug_counter >= 30) {
    //   debug();
    //   debug_counter = 0;
    // }


    // No start mod
    if (started == true || digitalRead(start_mod) == 1) {
      pollSensors();
      calculateState();
      writeMotors();
    } else {
      started = true;
      delay(4000);
    }
}

/**
 * Update Sensors
 */
void pollSensors() {
  leftIR->setValue(digitalRead(left_ir));
  flIR->setValue(digitalRead(fl_ir));
  midIR->setValue(digitalRead(mid_ir));
  frIR->setValue(digitalRead(fr_ir));
  rightIR->setValue(digitalRead(right_ir));

  frLine->setValue(analogRead(fr_line));
  flLine->setValue(analogRead(fl_line));
  brLine->setValue(analogRead(br_line));
  blLine->setValue(analogRead(bl_line));

  // Serial.print("FR Line: ");
  // Serial.println(analogRead(fr_line));
  // delay(100);

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
  analogWrite(fr_move_forward, frMotor->getDirection() == 0 ? frMotor->getSpeed() : 0);
  analogWrite(fr_move_backward, frMotor->getDirection() == 1 ? frMotor->getSpeed() : 0);
  analogWrite(fl_move_forward, flMotor->getDirection() == 0 ? flMotor->getSpeed() : 0);
  analogWrite(fl_move_backward, flMotor->getDirection() == 1 ? flMotor->getSpeed() : 0);
  analogWrite(br_move_forward, brMotor->getDirection() == 0 ? brMotor->getSpeed() : 0);
  analogWrite(br_move_backward, brMotor->getDirection() == 1 ? brMotor->getSpeed() : 0);
  analogWrite(bl_move_forward, blMotor->getDirection() == 0 ? blMotor->getSpeed() : 0);
  analogWrite(bl_move_backward, blMotor->getDirection() == 1 ? blMotor->getSpeed() : 0);
}



/**
 * Debuggin' + Hyperparameters.
 * 
 * Turn on/off accordingly. Can also modify frequency of output inside of running loop
 */

bool ir_debug = true;
bool line_debug = true;
bool motor_debug = false;

void debug() {
  Serial.println("=========================");

  Serial.println("Debug loop: ");

  // IR Sensors
  if (ir_debug == true) {
    Serial.print("Left IR: ");
    Serial.println(leftIR->getValue());
    Serial.print("Front Left IR: ");
    Serial.println(flIR->getValue());
    Serial.print("Mid IR: ");
    Serial.println(midIR->getValue());
    Serial.print("Front Right IR: ");
    Serial.println(frIR->getValue());
    Serial.print("Right IR: ");
    Serial.println(rightIR->getValue());
  }

  // Line Sensors
  if (line_debug == true) {
    Serial.print("Front Left Line: ");
    Serial.println(flLine->getValue());
    Serial.print("Front Right Line: ");
    Serial.println(frLine->getValue());
    Serial.print("Back Left Line: ");
    Serial.println(blLine->getValue());
    Serial.print("Back Right Line: ");
    Serial.println(brLine->getValue());
  }
  
  // Motor States
  if (motor_debug == true) {
    Serial.print("FL Motor: ");
    Serial.print(flMotor->getSpeed());
    Serial.print("FR Motor: ");
    Serial.println(frMotor->getSpeed());
    Serial.print("BL Motor: ");
    Serial.print(blMotor->getSpeed());
    Serial.print("BR Motor: ");
    Serial.println(brMotor->getSpeed());
  }

  Serial.println("=========================");
}