#include <Arduino.h>

// Imports
#include "Robot/Algorithms.cpp"
#include "Robot/RobotActions.cpp"
#include "Enumerations/EnemyPos.cpp"

// Output Pins
const int leftPWM = 33;
const int leftDir = 32;
const int rightPWM = 31;
const int rightDir = 30;

// Input Pins
const int left90IR = 11;
const int right90IR = 20;
const int left60IR = 12;
const int right60IR = 19;
const int left45IR = 13;
const int right45IR = 18;
const int left30IR = 14;
const int right30IR = 17;
const int centerIR = 16;

const int frLine = 37;
const int flLine = 38;
const int brLine = 36;
const int blLine = 35;

// Array Info Storage
/**
  * IRSensor: [left90, left60, left45, left30, center, right30, right45, right60, right90]
  * LineSensor: [Front Left, Front Right, Back Right, Back Left]
  * MotorDriver: [Left, Right]
*/
int irArray[9]; // [0, 1]
int lineArray[4]; // [0, 1]
int driver[2]; // [-255, 255]

// Classes
Algorithms *algo;
RobotActions *action;

/**
 * Initializing
 */
void setup() {
  // Pin Outs
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  pinMode(rightDir, OUTPUT);

  // Pin Inputs
  pinMode(left90IR, INPUT);
  pinMode(right90IR, INPUT);
  pinMode(left60IR, INPUT);
  pinMode(right60IR, INPUT);
  pinMode(left45IR, INPUT);
  pinMode(right45IR, INPUT);
  pinMode(left30IR, INPUT);
  pinMode(right30IR, INPUT);
  pinMode(centerIR, INPUT);

  pinMode(frLine, INPUT);
  pinMode(flLine, INPUT);
  pinMode(brLine, INPUT);
  pinMode(blLine, INPUT);

  action = new RobotActions(0, 0);
  algo = new Algorithms(action);
}

void pollSensors() {
  // IR Sensor Update
  irArray[0] = digitalRead(left90IR);
  irArray[1] = digitalRead(left60IR);
  irArray[2] = digitalRead(left45IR);
  irArray[3] = digitalRead(left30IR);
  irArray[4] = digitalRead(centerIR);
  irArray[5] = digitalRead(right30IR);
  irArray[6] = digitalRead(right45IR);
  irArray[7] = digitalRead(right60IR);
  irArray[8] = digitalRead(right90IR);

  // Line Sensor Update
  lineArray[0] = digitalRead(flLine);
  lineArray[1] = digitalRead(frLine);
  lineArray[2] = digitalRead(brLine);
  lineArray[3] = digitalRead(blLine);
}

void calcState() {
  // Update States + Run Algorithm
  
}

void writeMotors() {
  // Future: Implement PID to avoid motor burnout
  analogWrite(leftPWM, abs(driver[0]));
  digitalWrite(leftDir, driver[0] > 0 ? 0 : 1);
  analogWrite(rightPWM, abs(driver[1]));
  digitalWrite(rightDir, driver[1] > 0 ? 0 : 1);
}

/**
 * World State Functions
 */
EnemyPos getEnemyPosition() {
  // Based on irArray
  if (irArray[4] == 1) {
    return FRONT;
  } else if (irArray[3] == 1 || irArray[2] == 1 || irArray[1] == 1 || irArray[0] == 1) {
    return LEFT;
  } else {
    return RIGHT;
  }
  return NONE;
}

int isOnLine() {
  // Based on lineArray
  for (int i = 0; i < sizeof(lineArray); i++) {
    if (lineArray[i] < 800) {
      return 1;
    }
  }
  return 0;
}

/**
 * Repeated method calling: Read, Update States, Write Output
 */
void loop() {
  pollSensors();
  calcState();
  writeMotors();
}

