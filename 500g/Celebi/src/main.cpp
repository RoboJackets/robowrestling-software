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

// define motor array
int motors[2] = {0,0};

// define sensor arrays
int line_sensors[4] = {0,0,0,0};
int ir_sensors[5] = {0,0,0,0,0};


// set up algorithms class
algorithms* algorithm;

//set up robot actions
robot_actions* robot;

//set up world state
world_state* world;

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

    //initialize timer
    draw_timer = new timer(millis());
    attack_timer = new timer(millis());

    //initialize world state
    world = new world_state(line_sensors, ir_sensors);

    //initialize robot actions
    robot = new robot_actions(motors);    

    //initialize strategy
    algorithm = new algorithms(robot, world, draw_timer, attack_timer);



    Serial.begin(9600);
    Serial.print("we are running\n");
    draw_timer -> set_action_timer(10);
    attack_timer -> set_action_timer(10);
    // wait for start signal
    // while (!digitalRead(StartMod)) {
    //   Serial.print(digitalRead(StartMod));
    //   Serial.println(" Waiting for start signal");
    // }
}

void loop() {
    pollSensors();

    updateState();
    // updateMotors();

    //listen for stop signal
    // if (!digitalRead(StartMod)) {
    //   while(true) {
    //     brake();
    //     Serial.println("braking");
    //   }
    // }
    // debug();
}

void pollSensors() {
  //read line sensors
  int left1 = analogRead(Leftline1);
  int left2 = analogRead(Leftline2);
  int right1 = analogRead(Rightline1);
  int right2 = analogRead(Rightline2);

  //if both are black, bin = 0
  //if just right is black, bin = 1
  //if just left is black, bin = 2
  //if both are white, bin = 3

  line_sensors[0] = left1 < 100 ? 1 : 0;
  line_sensors[1] = left2 < 100 ? 1 : 0;
  line_sensors[2] = right1 < 100 ? 1 : 0;
  line_sensors[3] = right2 < 100 ? 1 : 0;

  //read ir sensors
  ir_sensors[0] = digitalRead(Ldist);
  ir_sensors[1] = digitalRead(LMIDdist);
  ir_sensors[2] = digitalRead(CENTdist);
  ir_sensors[3] = digitalRead(RMIDdist);
  ir_sensors[4] = digitalRead(Rdist);

  draw_timer -> update_time(millis());
  attack_timer -> update_time(millis());
}

void updateState() {
  algorithm -> match_strategy();
}

/**
 * Implemented for Shorti's motordrivers to conform to the
 * simple motordriver with speed and direction.  
 */ 
void updateMotors() {
    if (motors[0] > 0) {  // if direction is forward
        analogWrite(LmotorPos, motors[0]);
        analogWrite(LmotorNeg, 0);
    } else {   // if direction is forward
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
  robot -> brake();
  updateMotors();
}

void debug() {
  printf(sizeof(int));
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
  Serial.println(line_sensors[0]);
  Serial.println(line_sensors[1]);

  Serial.print("line right: ");
  Serial.println(line_sensors[2]);
  Serial.println(line_sensors[3]);


  //distance sensors

  Serial.print("distance left: ");
  Serial.println(ir_sensors[0]);

  Serial.print("distance mid left: ");
  Serial.println(ir_sensors[1]);

  Serial.print("distance mid: ");
  Serial.println(ir_sensors[2]);

  Serial.print("distance mid right: ");
  Serial.println(ir_sensors[3]);

  Serial.print("distance right: ");
  Serial.println(ir_sensors[4]);


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