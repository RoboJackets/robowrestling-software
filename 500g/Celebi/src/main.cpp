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
#define StartMod 10 
#define LineLeft A1
#define LineRight A0


#define Rpos 11
#define Rneg 13
#define Lpos 6
#define Lneg A5
#define PWMLeft 3
#define PWMRight 5
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
robot_actions* robo_actions;

//set up algorithms
algorithms* algorithm;

//set up world state and robot state pointers
world_state* world;
robot_state* robot;

//filter
int print = 0;

// define functions
void updateMotors();
void pollSensors();
void updateState();
void debug();

void setup() {
    // define pinmodes
    pinMode(Rpos, OUTPUT);
    pinMode(Rneg, OUTPUT);
    pinMode(Lpos, OUTPUT);
    pinMode(Lneg, OUTPUT);
    pinMode(PWMLeft, OUTPUT);
    pinMode(PWMRight, OUTPUT);
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
    robo_actions = new robot_actions(leftMotorDriver, rightMotorDriver);
    

    //initialize world state
    world = new world_state(line_left, line_right, ir_left, ir_mid_left, ir_mid, ir_mid_right, ir_right);
    
    //initialize algorithm
    algorithm = new algorithms(robo_actions, world);

    //initialize robot actions
    robot = new robot_state(world, algorithm);

    Serial.begin(9600);
    Serial.print("we are running\n");
    // wait for start signal
    while (!digitalRead(StartMod)) {
      Serial.print(digitalRead(StartMod));
      Serial.println(" Waiting for start signal");
    }
}

void loop() {
    pollSensors();
    updateState();
    updateMotors();

    // listen for stop signal
    if (!digitalRead(StartMod)) {
      while(true) {
        // brake()
        Serial.println("braking");
      }
    }
    debug();
    
}

void pollSensors() {
  //read line sensors
  line_left -> set_value(analogRead(LineLeft));
  line_right -> set_value(analogRead(LineRight));

  //read ir sensors
  ir_left -> set_ir_sensor(digitalRead(Lside));
  ir_mid_left -> set_ir_sensor(digitalRead(Lsensor));
  ir_mid -> set_ir_sensor(digitalRead(MSensor));
  ir_mid_right -> set_ir_sensor(digitalRead(Rsensor));
  ir_right -> set_ir_sensor(digitalRead(Rside));
}

void updateState() {
  robot -> runAlgorithm();
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
    int leftDirection = leftMotorDriver->get_direction();
    int leftSpeed = leftMotorDriver->get_speed();

    if (leftDirection == 1) {  // if direction is forward
        analogWrite(Lpos, 250);
        analogWrite(Lneg, 0);
    } else {                    // if direction is back
        analogWrite(Lpos, 0);
        analogWrite(Lneg, 250);
    }
    analogWrite(PWMLeft, leftSpeed);

    int rightDirection = rightMotorDriver->get_direction();
    int rightSpeed = rightMotorDriver->get_speed();

    if (rightDirection == 1) {  // if direction is forward
        analogWrite(Rpos, 250);
        analogWrite(Rneg, 0);
    } else {                    // if direction is back
        analogWrite(Rpos, 0);
        analogWrite(Rneg, 250);
    }
    analogWrite(PWMRight, rightSpeed);
}

void debug() {
  //delay(500);
  Serial.println("\n\n*****************");
  //sensors
  // Serial.println("sensors:");
  Serial.print("line left: ");
  Serial.println(line_left -> get_value());

  Serial.print("line right: ");
  Serial.println(line_right -> get_value());


  // Serial.print("distance left: ");
  // Serial.println(line_right -> get_value());

  // Serial.print("distance mid left: ");
  // Serial.println(ir_mid_left -> get_ir_sensor());

  // Serial.print("distance mid: ");
  // Serial.println(ir_mid -> get_ir_sensor());

  // Serial.print("distance mid right: ");
  // Serial.println(ir_mid_right -> get_ir_sensor());

  // Serial.print("distance right: ");
  // Serial.println(ir_right -> get_ir_sensor());

  // motors
  // Serial.println("motors:");

  // Serial.print("left motor direction: ");
  // Serial.println(leftMotorDriver -> get_direction());

  // Serial.print("right motor directtion: ");
  // Serial.println(rightMotorDriver -> get_direction());

  // Serial.print("left motor speed: ");
  // Serial.println(leftMotorDriver -> get_speed());

  // Serial.print("right motor speed: ");
  // Serial.println(rightMotorDriver -> get_speed());
  Serial.println("*****************");
}