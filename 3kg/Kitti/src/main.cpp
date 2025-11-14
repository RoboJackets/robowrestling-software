/**
 * Updating Kitti's main.cpp to fit Joe's robot
 */

#include <Arduino.h>

#include "World/World_State.hpp"
#include "Robot/Robot_Actions.hpp"
#include "World/Timer.hpp"
#include "Enums/line_states.hpp"
#include "Enums/enemy_states.hpp"
#include "Robot/Algorithms.hpp"

// Pins definitions
#define start_mod 10

#define LPos 6
#define LNeg A5
#define RPos 13
#define RNeg 11
#define left_speed 5
#define right_speed 3

#define line_left A0
#define line_right A1

#define ir_side_left 12
#define ir_front_left 8
#define ir_front_right 4
#define ir_side_right 2

// Arrays
/**
 * Motors: [Left, Right]
 * Line Sensors: [Left, Righ]
 * IR Sensors: [SideLeft, FrontLeft, FrontRight, SideRight]
 */
int motors[2] = {0, 0};
int line_sensors[2] = {0, 0};
int ir_sensors[4] = {0, 0, 0, 0};

// Class instances
WorldState* world;
RobotActions* action;
Algorithms* algo;
Timer* timer;


// Function declarations
void pollSensors();
void updateMotors();
void updateState();

/**
 * Set up structure of the code.
 */
void setup() {
  // put your setup code here, to run once
  pinMode(RPos, OUTPUT);
  pinMode(RNeg, OUTPUT);
  pinMode(LPos, OUTPUT);
  pinMode(LNeg, OUTPUT);
  pinMode(left_speed, OUTPUT);
  pinMode(right_speed, OUTPUT);

  pinMode(line_left, INPUT);
  pinMode(line_right, INPUT);

  pinMode(ir_side_left, INPUT);
  pinMode(ir_front_left, INPUT);
  pinMode(ir_front_right, INPUT);
  pinMode(ir_side_right, INPUT);

  // Allocate objects (was dereferencing uninitialized pointers which caused UB)
  world = new WorldState(line_sensors, ir_sensors);
  action = new RobotActions();
  timer = new Timer(millis());
  algo = new Algorithms(action, world, timer, NoneLine, NoneEnemy);
  Serial.begin(9600);
}

/**
 * Main loop
 */
void loop() {
  //if (digitalRead(start_mod) == HIGH) {
    pollSensors();
    updateState();
    updateMotors();
  //}
}

/**
 * Helper functions
 */

// Updating Sensor Arrays
void pollSensors() {
  // Poll line sensors
  line_sensors[0] = analogRead(line_left);
  line_sensors[1] = analogRead(line_right);

  // Poll IR sensors
  ir_sensors[0] = digitalRead(ir_side_left);
  ir_sensors[1] = digitalRead(ir_front_left);
  ir_sensors[2] = digitalRead(ir_front_right);
  ir_sensors[3] = digitalRead(ir_side_right);

  // Update World State Sensor Values and Update Timer
  world->update_sensors(line_sensors, ir_sensors);
  timer->updateTime();


  // Serial.print("Left IR: ");
  // Serial.println(digitalRead(ir_side_left));
  // Serial.print("Right IR: ");
  // Serial.println(ir_sensors[2]);
  Serial.println("Left Line: ");
  Serial.print(line_sensors[0]);
  Serial.print("Right Line: ");
  Serial.println(line_sensors[1]);
}

// Push to Motors
void updateMotors() {
  // Updating motors from robot actions
  // Serial.println("Left Motor: ");
  // Serial.print(motors[0]);
  // Serial.println("Right Motor: ");
  // Serial.println(motors[1]);

  // Ensure PWM is within 0-255
  int left_pwm = min(255, max(0, abs(motors[0])));
  int right_pwm = min(255, max(0, abs(motors[1])));

  // Left motor drive
  digitalWrite(LPos, motors[0] > 0 ? HIGH : LOW);
  digitalWrite(LNeg, motors[0] > 0 ? LOW : HIGH);
  analogWrite(left_speed, left_pwm);

  // Right motor drive
  digitalWrite(RPos, motors[1] > 0 ? HIGH : LOW);
  digitalWrite(RNeg, motors[1] > 0 ? LOW : HIGH);
  analogWrite(right_speed, right_pwm);
}

// Update Robot World State
void updateState() {
  algo->update_algo_state(world->line_check(), world->enemy_pos());
  algo->match_strategy();
  motors[0] = action->get_left_velocity();
  motors[1] = action->get_right_velocity();
}
