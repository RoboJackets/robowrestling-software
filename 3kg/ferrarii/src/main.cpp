#include <Arduino.h>
#include "RoboClaw.h"

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

#define address 0x80
RoboClaw roboclaw(&Serial8,10000);

void setup() {
  roboclaw.begin(38400);
}

void loop() {
  roboclaw.ForwardM1(address, 50);
  delay(10000);
  while (true) {
    roboclaw.ForwardM1(address, 0);
  }
}