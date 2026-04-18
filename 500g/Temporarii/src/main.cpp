/**
 * Temporarii Main File - Da Four-Wheel Drive
 */
#include <Arduino.h>
// #include <SparkFun_BMI270_Arduino_Library.h>
// #include <Wire.h>

/**
 * Imports
 */
#include "Robot/motorDriver.hpp"
#include "Robot/robotActions.hpp"
#include "Robot/robotState.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/Timer.hpp"
#include "Sensors/WorldState.hpp"
#include "Sensors/lineSensor.hpp"

/**
 * Pinouts
 */
const int fr_move_forward = 7;
const int fr_move_backward = 8;
const int fl_move_forward = 10;
const int fl_move_backward = 9;
const int br_move_forward = 11;
const int br_move_backward = 12;
const int bl_move_forward = 25;
const int bl_move_backward = 24;

const int left_ir = 32;
const int fl_ir = 30;
const int mid_ir = 6;
const int fr_ir = 3;
const int right_ir = 1;

const int fl_line = 26;
const int fr_line = 27;
const int bl_line = 40;
const int br_line = 16;

// Start mod
const int start_mod = 23;
bool started = false;
bool end = false;

// IMU
const int imu_pin1 = 33;
const int imu_pin2 = 34;
const int imu_scl = 19;
const int imu_sda = 18;

// BMI270 imu;
// float yaw = 0.0;
// unsigned long lastIMUTime = 0;

// Strategy Pin
const int strat_first = 39;
const int strat_second = 38;
int strategy_value = 0;

// LED Pins
const int fr_ir_led = 28;
const int fl_ir_led = 29;
const int left_ir_led = 31;
const int right_ir_led = 2;
const int mid_ir_led = 4;

const int fl_line_led = 41;
const int fr_line_led = 0;
const int bl_line_led = 35;
const int br_line_led = 17;

/**
 * Object Definition
 */
IrSensor* leftIR;
IrSensor* flIR;
IrSensor* midIR;
IrSensor* frIR;
IrSensor* rightIR;

LineSensor* flLine;
LineSensor* frLine;
LineSensor* blLine;
LineSensor* brLine;

MotorDriver* flMotor;
MotorDriver* frMotor;
MotorDriver* blMotor;
MotorDriver* brMotor;

RobotActions* action;
WorldState* world;
Algorithm* algo;

// Tempi 😃
RobotState* tempi;

Timer* timer;

// Prints debugging every few times to avoid spam
int debug_counter = 0;

// function definitions
void debug();
void writeMotors();
void pollSensors();
void calculateState();
void ledDisplay();
void stopMotors();
void updateIMU();

/**
 * Setup Pin Definitions
 */
void setup() {
  Serial.begin(9600);
  // delay(2000);

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

  pinMode(strat_first, INPUT);
  pinMode(strat_second, INPUT);

  pinMode(start_mod, INPUT);
  pinMode(strat_first, INPUT_PULLUP);
  pinMode(strat_second, INPUT_PULLUP);

  pinMode(left_ir_led, OUTPUT);
  pinMode(fl_ir_led, OUTPUT);
  pinMode(mid_ir_led, OUTPUT);
  pinMode(fr_ir_led, OUTPUT);
  pinMode(right_ir_led, OUTPUT);

  pinMode(fl_line_led, OUTPUT);
  pinMode(fr_line_led, OUTPUT);
  pinMode(bl_line_led, OUTPUT);
  pinMode(br_line_led, OUTPUT);

  // pinMode(imu_pin1, OUTPUT);
  // pinMode(imu_pin2, OUTPUT);
  // pinMode(imu_scl, INPUT);
  // pinMode(imu_sda, OUTPUT);

  // Setting up IMU
  // uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR;
  // Wire.begin();

  // while (imu.beginI2C(i2cAddress) != BMI2_OK)
  // {
  //   Serial.println("Error: BMI270 not connected, check wiring and I2C
  //   address");

  //   delay(1000);
  // }
  // Serial.println("BMI270");
  // Wire.setClock(100000);

  // Serial.println("Scanning I2C...");

  // for (uint8_t addr = 1; addr < 127; addr++) {
  //     Wire.beginTransmission(addr);
  //     if (Wire.endTransmission() == 0) {
  //         Serial.print("Found device at: 0x");
  //         Serial.println(addr, HEX);
  //     }
  // }

  // Serial.println("Initializing IMU...");

  // PASS WIRE OBJECT
  // int status = imu.beginI2C(0x68);

  // Serial.print("IMU status: ");
  // Serial.println(status);

  // if (status != BMI2_OK) {
  //     Serial.println("BMI270 initialization failed");
  // }

  // delay(200); // IMPORTANT

  // lastIMUTime = millis();
  // yaw = 0;

  flIR = new IrSensor();
  frIR = new IrSensor();
  midIR = new IrSensor();
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

  IrSensor* irSensors[5] = {leftIR, flIR, midIR, frIR, rightIR};
  LineSensor* lineSensors[4] = {blLine, flLine, frLine, brLine};

  // Setting up class structure
  action = new RobotActions(blMotor, flMotor, frMotor, brMotor);
  world = new WorldState(irSensors, lineSensors);
  timer = new Timer(millis());
  algo = new Algorithm(action, timer);
  tempi = new RobotState(world, algo);

  Serial.println("Starting Setup");
}

/**
 * Main loop
 */
void loop() {
  // 5 Seconds before start for comp
  // Start Mod -- Turn this on if you have a start module
  if (digitalRead(start_mod) == 1) {
    if (started) {
      pollSensors();
      calculateState();
      writeMotors();
    } else {
      started = true;
      // delay(5000);
    }
  } else {
    stopMotors();
  }

  // Debug
  // debug_counter++;
  // if (debug_counter >= 200)
  // {
  //   debug();
  //   debug_counter = 0;
  // }

  // No start mod -- Turn this on if you don't have a start module
  // if (started == true) {
  //   pollSensors();
  //   calculateState();
  //   writeMotors();
  // } else {
  //   started = true;
  //   delay(4000);
  // }

  // pollSensors();
  // calculateState();
  // writeMotors();

  // Serial.println(yaw);
  // delay(500);
  // imu.getSensorData();
  // Serial.print("Rotation: ");
  // Serial.print(imu.data.gyroX, 3);
  // delay(500);
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

  int val1 = (digitalRead(strat_first) == HIGH) ? 0 : 1;
  int val2 = (digitalRead(strat_second) == HIGH) ? 0 : 1;
  Serial.println(val1);
  Serial.println(val2);

  strategy_value = 2 * val2 + val1;

  // Show LED Displays for which ones are on
  ledDisplay();
  // updateIMU();
  timer->updateTime();
}

/**
 * Calc State using algorithm
 */
void calculateState() { tempi->runAlgorithm(strategy_value); }

/**
 * Write to motors
 */
void writeMotors() {
  // 0: forward, 1: backward
  analogWrite(fr_move_forward,
              frMotor->getDirection() == 0 ? frMotor->getSpeed() : 0);
  analogWrite(fr_move_backward,
              frMotor->getDirection() == 1 ? frMotor->getSpeed() : 0);

  analogWrite(fl_move_forward,
              flMotor->getDirection() == 0 ? flMotor->getSpeed() : 0);
  analogWrite(fl_move_backward,
              flMotor->getDirection() == 1 ? flMotor->getSpeed() : 0);

  analogWrite(br_move_forward,
              brMotor->getDirection() == 0 ? brMotor->getSpeed() : 0);
  analogWrite(br_move_backward,
              brMotor->getDirection() == 1 ? brMotor->getSpeed() : 0);

  analogWrite(bl_move_forward,
              blMotor->getDirection() == 0 ? blMotor->getSpeed() : 0);
  analogWrite(bl_move_backward,
              blMotor->getDirection() == 1 ? blMotor->getSpeed() : 0);
}

void ledDisplay() {
  // IR Sensor LED
  if (leftIR->getValue() == 1) {
    digitalWrite(left_ir_led, 1);
  } else {
    digitalWrite(left_ir_led, 0);
  }

  if (flIR->getValue() == 1) {
    digitalWrite(fl_ir_led, 1);
  } else {
    digitalWrite(fl_ir_led, 0);
  }

  if (midIR->getValue() == 1) {
    digitalWrite(mid_ir_led, 1);
  } else {
    digitalWrite(mid_ir_led, 0);
  }

  if (frIR->getValue() == 1) {
    digitalWrite(fr_ir_led, 1);
  } else {
    digitalWrite(fr_ir_led, 0);
  }

  if (rightIR->getValue() == 1) {
    digitalWrite(right_ir_led, 1);
  } else {
    digitalWrite(right_ir_led, 0);
  }

  // Line Sensor LED
  if (flLine->getValue() <= 500) {
    digitalWrite(fl_line_led, 1);
  } else {
    digitalWrite(fl_line_led, 0);
  }
  if (frLine->getValue() <= 500) {
    digitalWrite(fr_line_led, 1);
  } else {
    digitalWrite(fr_line_led, 0);
  }
  if (blLine->getValue() <= 500) {
    digitalWrite(bl_line_led, 1);
  } else {
    digitalWrite(bl_line_led, 0);
  }
  if (brLine->getValue() <= 500) {
    digitalWrite(br_line_led, 1);
  } else {
    digitalWrite(br_line_led, 0);
  }
}

void stopMotors() {
  analogWrite(fr_move_forward, 0);
  analogWrite(fr_move_backward, 0);

  analogWrite(fl_move_forward, 0);
  analogWrite(fl_move_backward, 0);

  analogWrite(br_move_forward, 0);
  analogWrite(br_move_backward, 0);

  analogWrite(bl_move_forward, 0);
  analogWrite(bl_move_backward, 0);
}

// void updateIMU() {
//     static unsigned long lastRead = 0;
//     if (millis() - lastRead < 20) return;
//     lastRead = millis();

//     int8_t status = imu.getSensorData();

//     if (status != BMI2_OK) {
//         Serial.print("IMU read error: ");
//         Serial.println(status);
//         return;
//     }

//     float gyroZ = imu.data.gyroZ;

//     unsigned long now = millis();
//     float dt = (now - lastIMUTime) / 1000.0;
//     lastIMUTime = now;

//     yaw += gyroZ * dt;

//     Serial.print("gyroZ: ");
//     Serial.print(gyroZ);
//     Serial.print(" yaw: ");
//     Serial.println(yaw);
// }

/**
 * Debuggin' + Hyperparameters.
 *
 * Turn on/off accordingly. Can also modify frequency of output inside of
 * running loop
 */

bool strat_debug = true;
bool ir_debug = true;
bool line_debug = false;
bool motor_debug = false;

void debug() {
  Serial.println("=========================");

  Serial.println("Debug loop: ");

  // Strategy
  if (strat_debug == true) {
    Serial.print("Strategy: ");
    Serial.println(strategy_value);
  }

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
  delay(100);
}