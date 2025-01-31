/**
 * Joe
 * File that outlines Shorti's main
 * 1/30/2025
 */

#include <Arduino.h>

// imports
#include "robot/motor_driver.hpp"
#include "robot/algorithms.hpp"
#include "robot/robot_actions.hpp"
#include "robot/robot_state.hpp"

#include "world/world_state.hpp"
#include "world/sensors/ir_sensor.hpp"
#include "world/sensors/line_sensor.hpp"

// pinouts
#define Lside 12
#define Lsensor 8
#define Rside 2
#define Rsensor 4
#define MSensor 7
#define RMsensor 9
#define LMsensor 13
#define StartMod 10
#define Rpos 6
#define Rneg 11
#define Lpos 3
#define Lneg 5
#define switch1 A6
#define switch2 A7

 
// define objects
motor_driver *leftMotorDriver;
motor_driver *rightMotorDriver;

//set up pointers to software sensors and motors
//set up line sensors
line_sensor* line_left;
line_sensor* line_right;
//set up ir sensors
ir_sensor* ir_left;
ir_sensor* ir_mid_left;
ir_sensor* ir_mid;
ir_sensor* ir_mid_right;
ir_sensor* ir_right;

//set up robot actions
robot_actions* actions;
//set up world state and robot state pointers
world_state* world;
robot_state* robot;

//filter
int print = 0;

// define functions
void updateMotors();

void setup() {
    // define pinmodes
    pinMode(Rpos, OUTPUT);
    pinMode(Rneg, OUTPUT);
    pinMode(Lpos, OUTPUT);
    pinMode(Lneg, OUTPUT);
    pinMode(StartMod, INPUT);
    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);

    // instantiate objects
    leftMotorDriver = new motor_driver();
    rightMotorDriver = new motor_driver();

    //initialize line sensors
    line_left = new line_sensor(0);
    line_right = new line_sensor(0);

    //initialize distance sensors
    ir_left = new ir_sensor(false);
    ir_mid_left = new ir_sensor(false);
    ir_mid = new ir_sensor(false);
    ir_mid_right = new ir_sensor(false);
    ir_right = new ir_sensor(false);

    //initialize robot actions
    actions = new robot_actions()

    //initialize world state and robot actions
    world = new world_state(line_left, line_right, ir_left, ir_mid_left, ir_mid, ir_mid_right, ir_right);
    robot = new robot_actions(left_motor, right_motor);

    Serial.begin(9600);
    Serial.print("we are running\n");
    // wait for start signal
    while (!digitalRead(StartMod)) {
      Serial.print(digitalRead(StartMod));
      Serial.println(" Waiting for start signal");
    }
}

void loop() {
    pollSensors()
    updateState()
    updateMotors();

    // listen for stop signal
    if (!digitalRead(StartMod)) {
      while(true) {
        // brake()
        Serial.println("braking");
      }
    }
    debug()
    
}

void pollSensors() {
  //read line sensors
  line_left -> set_value(analogRead(Lside));
  line_right -> set_value(analogRead(Rside));

  //read ir sensors
  ir_left -> set_ir_sensor(digitalRead(Lsensor));
  ir_mid_left -> set_ir_sensor(digitalRead(LMsensor));
  ir_mid -> set_ir_sensor(digitalRead(MSensor));
  ir_mid_right -> set_ir_sensor(digitalRead(RMsensor));
  ir_right -> set_ir_sensor(digitalRead(Rsensor));
}

void updateState() {
  robot_state -> runAlgorithm();
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
    int leftDirection = leftMotorDriver->get_direction();
    int leftSpeed = leftMotorDriver->get_speed();

    if (leftDirection == 1) {  // if direction is forward
        analogWrite(Lpos, leftSpeed);
        analogWrite(Lneg, 0);
    } else {                    // if direction is back
        analogWrite(Lpos, 0);
        analogWrite(Lneg, leftSpeed);
    }

    int rightDirection = rightMotorDriver->get_direction();
    int rightSpeed = rightMotorDriver->get_speed();

    if (rightDirection == 1) {  // if direction is forward
        analogWrite(Rpos, rightSpeed);
        analogWrite(Rneg, 0);
    } else {                    // if direction is back
        analogWrite(Rpos, 0);
        analogWrite(Rneg, rightSpeed);
    }
}

void debug() {
  if (print == 10) {
    //sensors
    Serial.println("sensors:\n");
    Serial.println("  line left: %d\n", line_left -> get_value);
    Serial.println("  line right: %d\n", line_right -> get_value);


    Serial.println("  distance left: %d\n", ir_left -> get_value);
    Serial.println("  distance mid left: %d\n", ir_mid_left -> get_value);
    Serial.println("  distance mid: %d\n", ir_mid -> get_value);
    Serial.println("  distance mid right: %d\n", ir_mid_right -> get_value);
    Serial.println("  distance right: %d\n", ir_right -> get_value);

    //motors
    Serial.println("motors:\n");
    Serial.println("  left motor direction: %d\n", leftMotorDriver -> get_direction());
    Serial.println("  right motor directtion: %d\n", rightMotorDriver -> get_direction());
    Serial.println("  left motor speed: %d\n", leftMotorDriver -> get_speed());
    Serial.println("  right motor speed: %d\n", rightMotorDriver -> get_speed());
    
    print = 0;
  }
  print++;

}