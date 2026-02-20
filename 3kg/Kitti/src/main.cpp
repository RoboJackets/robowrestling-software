/*
    🍓🍓🍓
         ╱|、
         (˚ˎ 。7  
          |、˜〵          
         じしˍ,)ノ
*/

#include <Arduino.h>

#include "Robot/World_State.hpp"
#include "Robot/Robot_Actions.hpp"
#include "Robot/Algorithms.hpp"
#include "Robot/Timer.hpp"
#include "Enums/line_states.hpp"
#include "Enums/enemy_states.hpp"

// Pins definitions
#define start_mod 13

#define left_pwm 37
#define left_dir_forward 0
#define left_dir_backward 0
#define right_pwm 33
#define right_dir_forward 0
#define right_dir_backward 0

#define line_fl 10
#define line_fr 11
#define line_bl 12
#define line_br 26

#define ir_back 7
#define ir_left 6
#define ir_left45 2
#define ir_front_left 3
#define ir_analog_transmit 20
#define ir_analog_receive 21
#define ir_front_right 4
#define ir_right45 5
#define ir_right 1

#define algo_pin1 38
#define algo_pin2 39
#define algo_pin3 40

// Arrays
/**
 * Motors: [Left, Right]
 * Line Sensors: [Front Left, Front Right, Back Right, Back Left]
 * IR Sensors: [Back, Left 90, Left 45, Front Left, Front Right, Right 45, Right 90]
 * IR Analog: Front Analog
 */
int motors[2] = {0, 0};
int line_sensors[4] = {0, 0, 0, 0};
int ir_sensors[7] = {0, 0, 0, 0, 0, 0, 0};
int ir_middle = 0;

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
  // Setup code for initialization of program
  pinMode(INPUT, start_mod);

  pinMode(INPUT, line_fl);
  pinMode(INPUT, line_fr);
  pinMode(INPUT, line_bl);
  pinMode(INPUT, line_br);

  pinMode(INPUT, ir_back);
  pinMode(INPUT, ir_left);
  pinMode(INPUT, ir_left45);
  pinMode(INPUT, ir_front_left);
  pinMode(INPUT, ir_front_right);
  pinMode(INPUT, ir_right45);
  pinMode(INPUT, ir_right);

  pinMode(INPUT, ir_analog_receive);
  pinMode(OUTPUT, ir_analog_transmit);

  pinMode(OUTPUT, left_pwm);
  pinMode(OUTPUT, left_dir_forward);
  pinMode(OUTPUT, left_dir_backward);
  pinMode(OUTPUT, right_pwm);
  pinMode(OUTPUT, right_dir_forward);
  pinMode(OUTPUT, right_dir_backward);

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
  line_sensors[0] = analogRead(line_fl);
  line_sensors[1] = analogRead(line_fr);
  line_sensors[2] = analogRead(line_br);
  line_sensors[3] = analogRead(line_bl);

  // Poll IR sensors
  ir_sensors[0] = digitalRead(ir_back);
  ir_sensors[1] = digitalRead(ir_left);
  ir_sensors[2] = digitalRead(ir_left45);
  ir_sensors[3] = digitalRead(ir_front_left);
  ir_sensors[4] = digitalRead(ir_front_right);
  ir_sensors[5] = digitalRead(ir_right45);
  ir_sensors[6] = digitalRead(ir_right);

  // Poll Analog sensor
  ir_middle = analogRead(ir_analog_receive);

  // Update World State Sensor Values and Update Timer
  world->update_sensors(line_sensors, ir_sensors);
  timer->updateTime();
}

// Push to Motors
void updateMotors() {
  // Ensure PWM is within 0-255
  int left_speed = min(255, max(0, abs(motors[0])));
  int right_speed = min(255, max(0, abs(motors[1])));

  // Left motor drive
  digitalWrite(left_dir_forward, motors[0] > 0 ? HIGH : LOW);
  digitalWrite(left_dir_backward, motors[0] > 0 ? LOW : HIGH);
  analogWrite(left_pwm, left_speed);

  // Right motor drive
  digitalWrite(right_dir_forward, motors[1] > 0 ? HIGH : LOW);
  digitalWrite(right_dir_backward, motors[1] > 0 ? LOW : HIGH);
  analogWrite(left_pwm, right_speed);
}

// Update Robot World State
void updateState() {
  algo->update_algo_state(world->line_check(), world->enemy_pos());
  algo->match_strategy();
  motors[0] = action->get_left_velocity();
  motors[1] = action->get_right_velocity();
}
