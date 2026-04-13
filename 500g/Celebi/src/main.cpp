/**
 * Celebi's main
 */


// imports

#include <Arduino.h>

#include "robot/algorithms.hpp"
#include "robot/robot_actions.hpp"

#include "world/world_state.hpp"
#include "world/timer.hpp"

// pinouts
#define Leftline A0
#define Rightline A4

#define Rdist 1
#define RMIDdist 2
#define CENTdist 4
#define LMIDdist 7
#define Ldist 12
#define StartMod 13
#define StartButton 8

#define RmotorPos 5
#define RmotorNeg 6
#define LmotorPos 10
#define LmotorNeg 9



int i = 0;

// define motor array
int motors[2] = {0,0};

// define sensor arrays
int line_sensors[2] = {0,0};
int ir_sensors[5] = {0,0,0,0,0};


// set up algorithms class
algorithms* algorithm;

//set up robot actions
robot_actions* robot;

//set up world state
world_state* world;

timer *draw_timer;
timer *match_start_timer;
timer *swerve_timer;

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
    pinMode(Leftline, INPUT);
    pinMode(Rightline, INPUT);
    pinMode(Ldist, INPUT);
    pinMode(LMIDdist, INPUT);
    pinMode(CENTdist, INPUT);
    pinMode(RMIDdist, INPUT);
    pinMode(Rdist, INPUT);
    pinMode(StartMod, INPUT);
    pinMode(StartButton, INPUT);

    //initialize timer
    draw_timer = new timer(millis());
    match_start_timer = new timer(millis());
    swerve_timer = new timer(millis());

    //initialize world state
    world = new world_state(line_sensors, ir_sensors);

    //initialize robot actions
    robot = new robot_actions(motors);    

    //initialize strategy
    algorithm = new algorithms(robot, world, draw_timer, match_start_timer, swerve_timer);

    // Serial.begin(9600);
    // Serial.print("we are running\n");
    draw_timer->set_action_timer(10);
    swerve_timer->set_action_timer(10);
    
    // wait for start signal
    // while (!digitalRead(StartMod)) {
    //   ;
    // }


    // while (!digitalRead(StartButton)) {
    //   Serial.println("waiting");
    // }
    // delay(5000);
    match_start_timer->update_time(millis());
    match_start_timer->set_action_timer(150);
}

void loop() {
    pollSensors();
    updateState();
    updateMotors();

    // listen for stop signal
    // if (!digitalRead(StartMod)) {
    //   while(true) {
    //     brake();
    //   }
    // }
    debug();
}

void pollSensors() {
  //read line sensors
  int left = analogRead(Leftline);
  int right = analogRead(Rightline);

  //if both are black, bin = 0
  //if just right is black, bin = 1
  //if just left is black, bin = 2
  //if both are white, bin = 3

  line_sensors[0] = left < 100 ? 1 : 0;
  line_sensors[1] = right < 100 ? 1 : 0;


  //read ir sensors
  ir_sensors[0] = digitalRead(Ldist);
  ir_sensors[1] = digitalRead(LMIDdist);
  ir_sensors[2] = digitalRead(CENTdist);
  ir_sensors[3] = digitalRead(RMIDdist);
  ir_sensors[4] = digitalRead(Rdist);

  draw_timer->update_time(millis());
  match_start_timer->update_time(millis());
  swerve_timer->update_time(millis());
}

void updateState() {
  algorithm->match_strategy();
  // algorithm->test();
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 * Max speed is 255
 */ 
void updateMotors() {
  if (motors[0] > 0) {  // if direction is forward
      analogWrite(LmotorPos, motors[0]);
      analogWrite(LmotorNeg, 0);
  } else {   // if direction is backward
      analogWrite(LmotorPos, 0);
      analogWrite(LmotorNeg, abs(motors[0]));
  }

  if (motors[1] > 0) {  // if direction is forward
      analogWrite(RmotorPos, motors[1]);
      analogWrite(RmotorNeg, 0);
  } else {                    // if direction is back
      analogWrite(RmotorPos, 0);
      analogWrite(RmotorNeg, abs(motors[1]));
  }
}

void brake() {
  robot->brake();
  updateMotors();
}

void debug() {
  if (millis() % 100 != 0) {
    return;
  }
  // Serial.println("\n\n*****************");
  
  // Start Modules
  // Serial.print("start mod: ");
  // Serial.println(digitalRead(StartMod));
  
  //Timer debugging

  // Serial.print("action timer has gone off: ");
  // Serial.println(thymer->check_action_time());
  // Serial.print("time since match start: ");
  // Serial.println(thymer->check_match_time());
  // Serial.print("millies: ");
  // Serial.println(millis());
  // Serial.print("action timer started at: ");
  // Serial.println(attack_timer->get_action_start());
  // Serial.print("current time from timer: ");
  // Serial.print("timer status: ");
  // Serial.println(match_start_timer->get_timer_state());
  
  
  // line sensors
  
  // Serial.println(line_sensors[0]);
  // Serial.println(line_sensors[1]);


  //distance sensors

  // Serial.print("distance left: ");
  // Serial.println(ir_sensors[0]);

  // Serial.print("distance mid left: ");
  // Serial.println(ir_sensors[1]);

  // Serial.print("distance mid: ");
  // Serial.println(ir_sensors[2]);

  // Serial.print("distance mid right: ");
  // Serial.println(ir_sensors[3]);

  // Serial.print("distance right: ");
  // Serial.println(ir_sensors[4]);


  // motors

  // Serial.println("motors:");

  // Serial.print("left motor: ");
  // Serial.println(motors[0]);

  // Serial.print("right motor: ");
  // Serial.println(motors[1]);


  //state
  // Serial.println(world ->enemy_pos());
  
  
  // Serial.println("*****************");
}