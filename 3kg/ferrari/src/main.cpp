#include <Arduino.h>
#include "robot/DefensiveStrat.h"

//Constants for the pin numbers
//* * * pins for motor drivers
const int MD_IN1 = A14;
const int MD_IN2 = A15;
//* * * pins for the omron sensors
const int FRONT_IR = 10;
const int RIGHT30_IR = 1;
const int RIGHT45_IR = 3;
const int RIGHT60_IR = 2;
const int RIGHT90_IR = 0;
const int LEFT30_IR = 28;
const int LEFT45_IR = 12;
const int LEFT60_IR = 11;
const int LEFT90_IR = 29;
//* * * pins for line sensor on the plow
const int PLOWLINE_MID = 20;
const int PLOWLINE_LEFT = 16;
const int PLOWLINE_RIGHT = 17;
//* * * pins for line sensors that are on the bot
const int LINEBACK_LEFT1 = 41;
const int LINEBACK_LEFT2 = 40;
const int LINEBACK_RIGHT1 = 21;
const int LINEBACK_RIGHT2 = 23;
const int LINEFRONT_LEFT1 = 26;
const int LINEFRONT_LEFT2 = 27;
const int LINEFRONT_RIGHT1 = 15;
const int LINEFRONT_RIGHT2 = 14;
//* * * LCD, IMU and Start Module, button
const int START_PIN = 33;
const int BUTTON_PIN = 4;


void setup() {


}

void loop() {

}
