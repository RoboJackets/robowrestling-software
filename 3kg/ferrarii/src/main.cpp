#include <Arduino.h>
#include "RoboClaw.h"
#include "LineSensor.hpp"
#include "IRSensor.hpp"
#include "MotorDriver.hpp"
#include "RobotActions.hpp"
#include "WorldState.hpp"
#include "Brazil.hpp"
#include "Strat.hpp"

// Line Sensors
const int LN_RB2 = 22;
const int LN_RB1 = 21;
const int LN_LB2 = 20;
const int LN_LB1 = 19;
const int LN_RF2 = 18;
const int LN_RF1 = 17;
const int LN_LF2 = 16;
const int LN_LF1 = 15;

// IR Sensors
const int IR_F = 12;
const int IR_30L = 26;
const int IR_60L = 27;
const int IR_90L = 28;
const int IR_30R = 29;
const int IR_60R = 30;
const int IR_90R = 31;
const int IR_B = 32;

// LCD
const int LCD_SCL = 24;
const int LCD_SDA = 25;

// Inputs
const int L_BUTTON = 41;
const int R_BUTTON = 40;

// Motor Inputs
const int S2 = 35;
const int S1 = 34;

// Start Module
const int S_MOD = 33;

LineSensor* LN_LF;
LineSensor* LN_RF;
LineSensor* LN_LB;
LineSensor* LN_RB;

IRSensor* _IR_F;
IRSensor* _IR_30L;
IRSensor* _IR_60L;
IRSensor* _IR_90L;
IRSensor* _IR_30R;
IRSensor* _IR_60R;
IRSensor* _IR_90R;
IRSensor* _IR_B;

MotorDriver* motorDriver;
WorldState* worldState;
RobotActions* robotActions; 

Brazil* brazil;
Strat* strat;

const int THRESHOLD = 700;

#define address 0x80
RoboClaw roboclaw(&Serial8,10000);

void debug();
void pollSensors(); 
void calculateState();
void writeMotors();

void setup() {
  pinMode(LN_RB2, INPUT);
  pinMode(LN_RB1, INPUT);
  pinMode(LN_LB2, INPUT);
  pinMode(LN_LB1, INPUT);
  pinMode(LN_RF2, INPUT);
  pinMode(LN_RF1, INPUT);
  pinMode(LN_LF2, INPUT);
  pinMode(LN_LF1, INPUT);

  LN_LF = new LineSensor(THRESHOLD);
  LN_RF = new LineSensor(THRESHOLD);
  LN_LB = new LineSensor(THRESHOLD);
  LN_RB = new LineSensor(THRESHOLD);

  _IR_F = new IRSensor();
  _IR_30L = new IRSensor();
  _IR_60L = new IRSensor();
  _IR_90L = new IRSensor();
  _IR_30R = new IRSensor();
  _IR_60R = new IRSensor();
  _IR_90R = new IRSensor();
  _IR_B = new IRSensor();

  motorDriver = new MotorDriver();
  robotActions = new RobotActions(motorDriver);
  worldState = new WorldState(
    LN_LF, 
    LN_RF, 
    LN_LB, 
    LN_RB,
    _IR_F,
    _IR_30L,
    _IR_60L,
    _IR_90L,
    _IR_30R,
    _IR_60R,
    _IR_90R,
    _IR_B
  );

  brazil = new Brazil(worldState, robotActions);
  strat = new Strat(worldState, robotActions);

  roboclaw.begin(38400);
    while (!digitalRead(S_MOD)) {
      Serial.print(digitalRead(S_MOD));
      Serial.println(" Waiting for start signal");
    }
}

void loop() {
  debug();
  pollSensors();
  calculateState();
  writeMotors();
  if (!digitalRead(S_MOD)) {
    while(true) {
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 0);
      Serial.println("braking");
    }
  }
}

void calculateState() {
  strat->run();
}

void pollSensors() {
  LN_LF->setValue(analogRead(LN_LF1), analogRead(LN_LF2));
  LN_RF->setValue(analogRead(LN_RF1), analogRead(LN_RF2));
  LN_LB->setValue(analogRead(LN_LB1), analogRead(LN_LB2));
  LN_RB->setValue(analogRead(LN_RB1), analogRead(LN_RB2));

  _IR_F->setValue(digitalRead(IR_F));
  _IR_30L->setValue(digitalRead(IR_30L));
  _IR_60L->setValue(digitalRead(IR_60L));
  _IR_90L->setValue(digitalRead(IR_90L));
  _IR_30R->setValue(digitalRead(IR_30R));
  _IR_60R->setValue(digitalRead(IR_60R));
  _IR_90R->setValue(digitalRead(IR_90R));
  _IR_B->setValue(digitalRead(IR_B));
}


// M1 is RIGHT
// M2 is LEFT
// BACKWARDS IS FORWARDS
void writeMotors() {
  if (motorDriver->getLeftDirection() == FORWARD) {
    roboclaw.BackwardM2(address, motorDriver->getLeftSpeed());
  }
  if (motorDriver->getLeftDirection() == BACKWARD) {
    roboclaw.ForwardM2(address, motorDriver->getLeftSpeed());
  }
  if (motorDriver->getRightDirection() == FORWARD) {
    roboclaw.BackwardM1(address, motorDriver->getLeftSpeed());
  }
  if (motorDriver->getRightDirection() == BACKWARD) {
    roboclaw.ForwardM1(address, motorDriver->getLeftSpeed());
  }
}

void debug() {
  if (false) { //debug line sensors
    Serial.print(analogRead(LN_LF2));
    Serial.print(" ");
    Serial.print(analogRead(LN_LF1));
    Serial.print(" ");
    Serial.print(analogRead(LN_RF2));
    Serial.print(" ");
    Serial.print(analogRead(LN_RF1));
    Serial.print(" ");
    Serial.print(analogRead(LN_RB2));
    Serial.print(" ");
    Serial.print(analogRead(LN_RB1));
    Serial.print(" ");
    Serial.print(analogRead(LN_LB2));
    Serial.print(" ");
    Serial.print(analogRead(LN_LB1));
    Serial.print(" ");
  }
  if (true) {
    Serial.print(LN_LF->getValue());
    Serial.print(LN_RF->getValue());
    Serial.print(LN_LB->getValue());
    Serial.print(LN_RB->getValue());
    Serial.print(" ");
  }
  if (true) {
    Serial.print(digitalRead(IR_F));
    Serial.print(digitalRead(IR_30L));
    Serial.print(digitalRead(IR_60L));
    Serial.print(digitalRead(IR_90L));
    Serial.print(digitalRead(IR_30R));
    Serial.print(digitalRead(IR_60R));
    Serial.print(digitalRead(IR_90R));
    Serial.print(digitalRead(IR_B));
    Serial.print(" ");
  }
  if (true) {
    Serial.print(motorDriver->getLeftDirection());
    Serial.print(motorDriver->getLeftSpeed());
    Serial.print(" ");
    Serial.print(motorDriver->getRightDirection());
    Serial.print(motorDriver->getRightSpeed());
  }
  Serial.println();
}

