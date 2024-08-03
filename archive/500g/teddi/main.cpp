#include <Arduino.h>

const int RIGHT_LINE_SENSOR = A1;
const int LEFT_LINE_SENSOR = A2;
const int BACK_LINE_SENSOR = A3;

const int LEFT_WHEEL_BACK = A5;
const int LEFT_WHEEL_FORWARD = A6;
const int RIGHT_WHEEL_BACK = A7;
const int RIGHT_WHEEL_FORWARD = A8;

const int LEFT_LONG_IR_SENSOR = A9;
const int RIGHT_LONG_IR_SENSOR = A10;
const int MIDDLE_LONG_IR_SEOSOR = A11;
const int LEFT_SHORT_IR_SENSOR = A12;
const int RIGHT_SHORT_IR_SENSOR = A13;

String state = "";
String lastIRSeen = "";

const int MAX_LINE_SENSOR_COUNTER = 5;
const int MAX_SUB_LINE_SENSOR_COUTNER = 2;
int rightLineSensorCounter = 0; //These counters are to keep track of how long what sensors have been on the line
int leftLineSensorCounter = 0;
int backLineSensorCounter = 0;

int escapeStateCounter = 0; /*This is a counter to keep track of how long the robot has been trying to get away of the line useing 1
                            particular movement.*/

const int LINE_SENSOR_HOT = 0;
const int LINE_SENSOR_COLD = 1023;

const int IR_SENSOR_HOT = 1023;
const int IR_SENSOR_COLD = 0;
const int IR_SENSOR_MIDDLE = 512;

const int WHEEL_MAX_SPEED = 1023;
const int WHEEL_HIGH_SPEED = 768;
const int WHEEL_MED_SPEED = 512;
const int WHEEL_MIN_SPEED = 256;
const int WHEEL_OFF = 0;
const int START_COUNTER_TIME = 3000;

const int ESCAPE_COUNTER_TIME = 1000;

void robotState();        //calls the correct method to execute actions
void checkCounter();      //checks the line sensor counters and will react accordingly
void checkPosition();     //checks if robot is on line, returns true if it is, returns false if it isnt.
void start();
void checkIR();
//void slam();              //moving towards enemy //implemented by track
void search();            //searching for enemy
void track();             //is called after slam to track enemy

void incrementEscapeCounter(int);   //time keeper for line escape sequence.
void assignMovement();
void backUp();            //left and right back fast
void backUpRight();       //left fast back right slow back
void backUpLeft();        //right fast back left slow back
void moveForward();       //left and right fast forwards
void moveForwardRight();  //left fast forwards right slow forwards
void moveForwardLeft();   //right fast forwards left slow forwards

//setup
void setup() {
  Serial.begin(9600);
  state = "start";
}

//loop
void loop() {
  robotState();
}

//provides the current task for the robot
void robotState() {
  checkCounter();
  checkPosition();
  checkIR();
  assignMovement();
}

void checkCounter() {
  if (analogRead(LEFT_LINE_SENSOR) == LINE_SENSOR_HOT) {
    leftLineSensorCounter++;
  } else {
    leftLineSensorCounter = 0;
  }
  if (analogRead(RIGHT_LINE_SENSOR) == LINE_SENSOR_HOT) {
    rightLineSensorCounter++;
  } else {
    rightLineSensorCounter = 0;
  }
  if (analogRead(BACK_LINE_SENSOR) == LINE_SENSOR_HOT) {
    backLineSensorCounter++;
  } else {
    backLineSensorCounter = 0;
  }
}

void checkPosition() {
  String currentState = state;
  if (leftLineSensorCounter >= MAX_LINE_SENSOR_COUNTER) {
    if (rightLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "backUp"; // both back fast
    }
    else if (backLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "forwardRight"; // left wheel fast foward // right wheel slow forward
    }
    else {
      state = "backUpLeft"; // right wheel fast back // left wheel slow back
    }
  }
  if (rightLineSensorCounter >= MAX_LINE_SENSOR_COUNTER) {
    if (leftLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "backUp"; // both back fast
    }
    else if (backLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "forwardLeft"; // right wheel fast forward // left wheel slow forward
    }
    else {
      state = "backUpRight"; // left wheel fast back // right wheel slow back
    }
  }
  if (backLineSensorCounter >= MAX_LINE_SENSOR_COUNTER) {
    if (rightLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "forwardLeft"; // right wheel fast foward // left wheel slow forward
    }
    else if (leftLineSensorCounter >= MAX_SUB_LINE_SENSOR_COUTNER) {
      state = "forwardRight"; // left wheel fast forward // right wheel slow forward
    }
    else {
      state = "forwards"; // both forwards fast
    }
  }
  if (!state.equals(currentState)) {
    escapeStateCounter = 0;
  }
}

void assignMovement() {
  if (state.equals("forwards")) {
    moveForward();
  }
  if (state.equals("forwardLeft")) {
    moveForwardLeft();
  }
  if (state.equals("forwardRight")) {
    moveForwardRight();
  }
  if (state.equals("backUp")) {
    backUp();
  }
  if (state.equals("backUpLeft")) {
    backUpLeft();
  }
  if (state.equals("backUpRight")) {
    backUpRight();
  }
  if (state.equals("start")) {
    start();
  }
  if (state.equals("search")) {
    search();
  }
  if (state.equals("track")) {
    track();
  }
}

void incrementEscapeCounter(int time) {
  escapeStateCounter++;
  delay(1);
  if (escapeStateCounter >= time) {
    escapeStateCounter = 0;
    state = "search";
  }
}

void moveForward() {
  analogWrite(LEFT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}
void start() {
  analogWrite(LEFT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  incrementEscapeCounter(START_COUNTER_TIME);
}
void moveForwardLeft() { //right fast forwards left slow forwards
  analogWrite(LEFT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_MIN_SPEED);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}
void moveForwardRight() { //left fast forwards right slow forwards
  analogWrite(LEFT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_MAX_SPEED);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_MIN_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}
void backUp() {
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_BACK, WHEEL_MAX_SPEED);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_MAX_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}
void backUpLeft() { //right fast back left slow back
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_BACK, WHEEL_MED_SPEED);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_MAX_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}
void backUpRight() { //left fast back right slow back
  analogWrite(LEFT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(RIGHT_WHEEL_FORWARD, WHEEL_OFF);
  analogWrite(LEFT_WHEEL_BACK, WHEEL_MAX_SPEED);
  analogWrite(RIGHT_WHEEL_BACK, WHEEL_MED_SPEED);
  incrementEscapeCounter(ESCAPE_COUNTER_TIME);
}

void search () { // if no sensors are seeing anything, go off whatever the last sensor is
  if (LEFT_LONG_IR_SENSOR < IR_SENSOR_MIDDLE 
  && MIDDLE_LONG_IR_SEOSOR < IR_SENSOR_MIDDLE
  && RIGHT_LONG_IR_SENSOR < IR_SENSOR_MIDDLE) {
    if (lastIRSeen != "") {
      if (lastIRSeen.equals("right")) {
        state = "forwardRight";
      } else { //lastIRSeen.equals("left")
        state = "forwardLeft";
      }
    } else { //lastIRSeen is empty
      state = "forwardRight";
    }
  } else { //A sensor is reading high
    state = "track";
  } 
}

void checkIR() {
  if (LEFT_LONG_IR_SENSOR > IR_SENSOR_MIDDLE) {
    lastIRSeen = "left";
  }
  if (RIGHT_LONG_IR_SENSOR > IR_SENSOR_MIDDLE) {
      lastIRSeen = "right";
  }
  if (MIDDLE_LONG_IR_SEOSOR > IR_SENSOR_MIDDLE) {
    lastIRSeen = "middle"; //yippeeee
  }
}

void track() {
  escapeStateCounter = 0; // just in case
  if (lastIRSeen.equals("left")) {
    moveForwardLeft();
  }
  if (lastIRSeen.equals("right")) {
    moveForwardRight();
  }
  if (lastIRSeen.equals("middle")) {
    moveForward();
  }
}
