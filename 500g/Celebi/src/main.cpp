/**
 * Celebi's main
 */


// imports

#include <Arduino.h>

#include "robot/motor_driver.hpp"
#include "robot/algorithms.hpp"
#include "robot/robot_actions.hpp"
#include "robot/robot_state.hpp"

#include "world/world_state.hpp"
#include "world/sensors/ir_sensor.hpp"
#include "world/sensors/line_sensor.hpp"
#include "world/sensors/timer.hpp"

// pinouts
#define Leftline1 16
#define Leftline2 17
#define Rightline1 18
#define Rightline2 19

#define Rdist 0
#define RMIDdist 1
#define CENTdist 7
#define LMIDdist 8
#define Ldist 28
#define StartMod 29

#define RmotorPos 3
#define RmotorNeg 4
#define LmotorPos 33
#define LmotorNeg 13

int i = 0;

// define objects
motor_driver *leftMotorDriver;
motor_driver *rightMotorDriver;

//set up pointers to software sensors and motors
//set up line sensors
line_sensor* line_left1;
line_sensor* line_left2;
line_sensor* line_right1;
line_sensor* line_right2;
//set up ir sensors
ir_sensor* ir_left;
ir_sensor* ir_mid_left;
ir_sensor* ir_mid;
ir_sensor* ir_mid_right;
ir_sensor* ir_right;

//set up robot actions
robot_actions* actions;

//set up algorithms
algorithms* algorithm;

//set up world state and robot state pointers
world_state* world;
robot_state* robot;

timer *draw_timer;
timer *attack_timer;

//filter
int print = 0;

// define functions
void updateMotors();
void pollSensors();
void updateState();
void brake();
void debug();

void setup() {
    // define pinmodes
    pinMode(LmotorNeg, OUTPUT);
    pinMode(LmotorPos, OUTPUT);
    pinMode(RmotorNeg, OUTPUT);
    pinMode(RmotorPos, OUTPUT);
    pinMode(Leftline1, INPUT);
    pinMode(Leftline2, INPUT);
    pinMode(Rightline1, INPUT);
    pinMode(Rightline2, INPUT);
    pinMode(Ldist, INPUT);
    pinMode(LMIDdist, INPUT);
    pinMode(CENTdist, INPUT);
    pinMode(RMIDdist, INPUT);
    pinMode(Rdist, INPUT);
    pinMode(StartMod, INPUT);

    // instantiate objects
    leftMotorDriver = new motor_driver();
    rightMotorDriver = new motor_driver();

    //initialize line sensors
    line_left1 = new line_sensor(0);
    line_left2 = new line_sensor(0);
    line_right1 = new line_sensor(0);
    line_right2 = new line_sensor(0);

    //initialize distance sensors
    ir_left = new ir_sensor(false);
    ir_mid_left = new ir_sensor(false);
    ir_mid = new ir_sensor(false);
    ir_mid_right = new ir_sensor(false);
    ir_right = new ir_sensor(false);

    //initialize timer
    draw_timer = new timer(millis());
    attack_timer = new timer(millis());

    //initialize robot actions
    actions = new robot_actions(leftMotorDriver, rightMotorDriver);
    
    //initialize world state
    world = new world_state(line_left1, line_left2, line_right1, line_right2, ir_left, ir_mid_left, ir_mid, ir_mid_right, ir_right);
    
    //initialize algorithm
    algorithm = new algorithms(actions, world, draw_timer, attack_timer);

    //initialize robot actions
    robot = new robot_state(world, algorithm);


    Serial.begin(9600);
    Serial.print("we are running\n");
    draw_timer -> set_action_timer(10);
    attack_timer -> set_action_timer(10);
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

    //listen for stop signal
    if (!digitalRead(StartMod)) {
      while(true) {
        brake();
        Serial.println("braking");
      }
    }
    debug();
    
}

void pollSensors() {
  //read line sensors
  line_left1 -> set_value(analogRead(Leftline1));
  line_left2 -> set_value(analogRead(Leftline2));
  line_right1 -> set_value(analogRead(Rightline1));
  line_right2 -> set_value(analogRead(Rightline2));

  //read ir sensors
  ir_left -> set_ir_sensor(digitalRead(Ldist));
  ir_mid_left -> set_ir_sensor(digitalRead(LMIDdist));
  ir_mid -> set_ir_sensor(digitalRead(CENTdist));
  ir_mid_right -> set_ir_sensor(digitalRead(RMIDdist));
  ir_right -> set_ir_sensor(digitalRead(Rdist));

  draw_timer -> update_time(millis());
  attack_timer -> update_time(millis());
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
    int leftSpeed = leftMotorDriver->get_speed() * .7;

    if (leftDirection == 1) {  // if direction is forward
        analogWrite(LmotorPos, leftSpeed);
        analogWrite(LmotorNeg, 0);
    } else {                    // if direction is forward
        analogWrite(LmotorPos, 0);
        analogWrite(LmotorNeg, leftSpeed);
    }


    int rightDirection = rightMotorDriver->get_direction();
    int rightSpeed = rightMotorDriver->get_speed();

    if (rightDirection == 1) {  // if direction is forward
        analogWrite(RmotorPos, rightSpeed);
        analogWrite(RmotorNeg, 0);
    } else {                    // if direction is back
        analogWrite(RmotorPos, 0);
        analogWrite(RmotorNeg, rightSpeed);
    }

}

void brake() {
  actions -> brake();
  updateMotors();
}

void debug() {
  i++;
  if (i < 1000) {
    return;
  } else {
    i = 0;
  }
  //delay(50);
  Serial.println("\n\n*****************");
  
  //Timer debugging

  // Serial.print("action timer has gone off: ");
  // Serial.println(thymer -> check_action_time());
  // Serial.print("time since match start: ");
  // Serial.println(thymer -> check_match_time());
  // Serial.print("millies: ");
  // Serial.println(millis());
  // Serial.print("action timer started at: ");
  // Serial.println(thymer -> get_action_start());
  // Serial.print("current time from timer: ");
  // Serial.println(thymer -> get_current_time());
  // Serial.print("timer status: ");
  // Serial.println(thymer -> get_timer_state());
  
  
  //line sensors
  
  Serial.println("sensors:");
  Serial.print("line left: ");
  Serial.println(line_left1 -> get_value());
  Serial.println(line_left2 -> get_value());

  Serial.print("line right: ");
  Serial.println(line_right1 -> get_value());
  Serial.println(line_right2 -> get_value());


  //distance sensors

  Serial.print("distance left: ");
  Serial.println(ir_right -> get_ir_sensor());

  Serial.print("distance mid left: ");
  Serial.println(ir_mid_left -> get_ir_sensor());

  Serial.print("distance mid: ");
  Serial.println(ir_mid -> get_ir_sensor());

  Serial.print("distance mid right: ");
  Serial.println(ir_mid_right -> get_ir_sensor());

  Serial.print("distance right: ");
  Serial.println(ir_right -> get_ir_sensor());


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


  //state
  //Serial.println(world ->enemy_pos());
  
  
  Serial.println("*****************");
}