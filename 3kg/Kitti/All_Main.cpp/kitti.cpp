/**
 * Kitti's original main.cpp
 */

#include <Arduino.h>

#include "Robot/World_State.hpp"
#include "Robot/Robot_Actions.hpp"
#include "Robot/Algorithms.hpp"
#include "Enums/line_states.hpp"
#include "Enums/enemy_states.hpp"

// Pins definitions
const int motor_left = 1;
const int motor_left_dir = 20;
const int motor_right = 2;
const int motor_right_dir = 21;

const int line_fl = 3;
const int line_fr = 4;
const int line_bl = 5;
const int line_br = 6;

const int ir_back_left = 7;
const int ir_left_back = 8;
const int ir_left_front = 9;
const int ir_left_mid = 10;
const int ir_mid = 11;
const int ir_right_mid = 12;
const int ir_right_front = 13;
const int ir_right_back = 14;
const int ir_back_right = 15;

// Arrays
/**
 * Motors: [Left, Right]
 * Line Sensors: [Front Left, Front Right, Back Left, Back Right]
 * IR Sensors: [Back Left, Left Back, Left Front, LeftMid, Mid, RightMid, Right Front, Right Back, Back Right]
 */
int motors[2] = {0, 0};
int line_sensors[4] = {0, 0, 0, 0};
int ir_sensors[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
// int lidar[3] = {0, 0, 0}; LIDAR uses DFRobot_TFmini library

// Class instances
WorldState* world;
RobotActions* action;
Algorithms* algo;

// Function declarations
void pollSensors();
void updateMotors();
void updateState();

/**
 * Set up structure of the code.
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor_left, OUTPUT);
  pinMode(motor_left_dir, OUTPUT);
  pinMode(motor_right, OUTPUT);
  pinMode(motor_right_dir, OUTPUT);

  pinMode(line_fl, INPUT);
  pinMode(line_fr, INPUT);
  pinMode(line_bl, INPUT);
  pinMode(line_br, INPUT);

  pinMode(ir_back_left, INPUT);
  pinMode(ir_left_back, INPUT);
  pinMode(ir_left_front, INPUT);
  pinMode(ir_left_mid, INPUT);
  pinMode(ir_mid, INPUT);
  pinMode(ir_right_mid, INPUT);
  pinMode(ir_right_front, INPUT);
  pinMode(ir_right_back, INPUT);
  pinMode(ir_back_right, INPUT);

  *world = WorldState(line_sensors, ir_sensors);
  *action = RobotActions();
  *algo = Algorithms(action, world, NoneLine, NoneEnemy);
}

/**
 * Main loop
 */
void loop() {
  pollSensors();
  updateState();
  updateMotors();
}

/**
 * Helper functions
 */

// Updating Sensor Arrays
void pollSensors() {
  // Poll line sensors
  line_sensors[0] = digitalRead(line_fl);
  line_sensors[1] = digitalRead(line_fr);
  line_sensors[2] = digitalRead(line_bl);
  line_sensors[3] = digitalRead(line_br);

  // Poll IR sensors
  ir_sensors[0] = digitalRead(ir_back_left);
  ir_sensors[1] = digitalRead(ir_left_back);
  ir_sensors[2] = digitalRead(ir_left_front);
  ir_sensors[3] = digitalRead(ir_left_mid);
  ir_sensors[4] = digitalRead(ir_mid);
  ir_sensors[5] = digitalRead(ir_right_mid);
  ir_sensors[6] = digitalRead(ir_right_front);
  ir_sensors[7] = digitalRead(ir_right_back);
  ir_sensors[8] = digitalRead(ir_back_right);

  // Poll LIDAR
  // lidar[0] = tfmini.getDistance();
  // lidar[1] = tfmini.getStrength();
  // lidar[2] = tfmini.getTemperature();

  // Update World State Sensor Values
  world->update_sensors(line_sensors, ir_sensors);
}

// Push to Motors
void updateMotors() {
  // Updating motors from robot actions
  analogWrite(motor_left, motors[0]);
  digitalWrite(motor_left_dir, motors[0] > 0 ? 0 : 1);
  analogWrite(motor_right, motors[1]);
  digitalWrite(motor_right_dir, motors[1] > 0 ? 0 : 1);
}

// Update Robot World State
void updateState() {
  algo->match_strategy();
  motors[0] = action->get_left_velocity();
  motors[1] = action->get_right_velocity();
}
