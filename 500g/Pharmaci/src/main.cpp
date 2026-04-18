#include <Arduino.h>
#include <IRSensor.h>
#include <LineSensor.h>
#include <MotorDriver.h>
#include <RobotActions.h>
#include <WorldState.h>
#include <RobotState.h>
#include <Servo.h>


IRSensor *leftIRSensor;
IRSensor *leftMiddleIRSensor;
IRSensor *middleIRSensor;
IRSensor *rightMiddleIRSensor;
IRSensor *rightIRSensor;
LineSensor *leftLineSensor;
LineSensor *rightLineSensor;
 
MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotActions *robotActions;
WorldState *worldState;
RobotState *robotState;

Servo servo;

// Shorti Pins




//    const int LEFT_IR_90 = 2;
//  const int LEFT_IR_45 = 3;
//  const int RIGHT_IR_90 = 5;
//  const int RIGHT_IR_45 = 8;
//  const int MIDDLE_IR = 4;

//  const int START_MODULE = 6;
// const int L_NEG = 1;
// const int L_POS = 0;
// const int R_POS = 28;
// const int R_NEG = 29;

//  const int LEFT_LINE = A6;
//  const int RIGHT_LINE = A7;

//     const int LEFT_IR_90 = 8;
//  const int LEFT_IR_45 = 5;
//  const int RIGHT_IR_90 = 2;
//  const int RIGHT_IR_45 = 3;
//  const int MIDDLE_IR = 4;

//  const int START_MODULE = 6;
// const int L_NEG = 1;
// const int L_POS = 0;
// const int R_POS = 28;
// const int R_NEG = 29;

//  const int LEFT_LINE = A6;
//  const int RIGHT_LINE = A7;

     const int LEFT_IR_90 = 5;
 const int LEFT_IR_45 = 3;
 const int RIGHT_IR_90 = 8;
 const int RIGHT_IR_45 = 4;
 const int MIDDLE_IR = 2;

 const int START_MODULE = 6;
const int L_NEG = 1;
const int L_POS = 0;
const int R_POS = 28;
const int R_NEG = 29;

 const int LEFT_LINE = A4;
 const int RIGHT_LINE = A7;

 const int DIP1 = 36;
const int DIP2 = 37;

int getDipMode() {
  int dip1 = !digitalRead(DIP1);
  int dip2 = !digitalRead(DIP2);
  return (dip2 << 1) | dip1;
}

void setup() {
  servo.attach(34);
  servo.write(0);

  // Serial.begin(9600);
    pinMode(R_POS, OUTPUT);
     pinMode(R_NEG, OUTPUT);
     pinMode(L_POS, OUTPUT);
     pinMode(L_NEG, OUTPUT);
     pinMode(LEFT_IR_90, INPUT);
     pinMode(LEFT_IR_45, INPUT);
     pinMode(MIDDLE_IR, INPUT);
     pinMode(RIGHT_IR_45, INPUT);
     pinMode(RIGHT_IR_90, INPUT);
     pinMode(LEFT_LINE, INPUT);
     pinMode(RIGHT_LINE, INPUT);
     pinMode(START_MODULE, INPUT);


  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver();
  robotActions = new RobotActions(leftMotorDriver, rightMotorDriver);
  leftIRSensor = new IRSensor();
  leftMiddleIRSensor = new IRSensor();
  middleIRSensor = new IRSensor();
  rightMiddleIRSensor = new IRSensor();
  rightIRSensor = new IRSensor();
  leftLineSensor = new LineSensor();
  rightLineSensor = new LineSensor();
  

  worldState = new WorldState(leftLineSensor, rightLineSensor, leftIRSensor, leftMiddleIRSensor, middleIRSensor, rightMiddleIRSensor, rightIRSensor);
  robotState = new RobotState(worldState, robotActions, leftMotorDriver, rightMotorDriver);
}


void updateMotors() {
     bool leftDirection = leftMotorDriver->getDirection();
     int leftSpeed = leftMotorDriver->getSpeed();
 
     if (leftDirection) {  // if direction is forward
        analogWrite(L_POS, leftSpeed);
        analogWrite(L_NEG, 0);
     } else {                    // if direction is back
        analogWrite(L_POS, 0);
        analogWrite(L_NEG, leftSpeed);
     }
 
     bool rightDirection = rightMotorDriver->getDirection();
     int rightSpeed = rightMotorDriver->getSpeed();
 
     if (rightDirection) {  // if direction is forward
        analogWrite(R_POS, rightSpeed);
        analogWrite(R_NEG, 0);
     } else {                    // if direction is back
        analogWrite(R_POS, 0);
        analogWrite(R_NEG, rightSpeed);
     }

 }

void pollSensors() {
  //implement proper velocity measurement D:
  leftIRSensor->setValue(digitalRead(LEFT_IR_90));
  middleIRSensor->setValue(digitalRead(MIDDLE_IR));
  rightIRSensor->setValue(digitalRead(RIGHT_IR_90));
  leftMiddleIRSensor->setValue(digitalRead(LEFT_IR_45));
  rightMiddleIRSensor->setValue(digitalRead(RIGHT_IR_45));
  leftLineSensor->setValue(analogRead(LEFT_LINE));
  rightLineSensor->setValue(analogRead(RIGHT_LINE));
  

}

void calculateState(int time) {
  robotState->calculateState(time);
}

const char* positionToString(Position pos) {
    switch (pos) {
        case Position::None: return "None";
        case Position::Left: return "Left";
        case Position::Left_Middle: return "Left_Middle";
        case Position::Left_Middle_Close: return "Left_Middle_Close";
        case Position::Middle_Close: return "Middle_Close";
        case Position::Middle_Far: return "Middle_Far";
        case Position::Right_Middle_Close: return "Right_Middle_Close";
        case Position::Right_Middle: return "Right_Middle";
        case Position::Right: return "Right";
        case Position::On_Line_Left: return "On_Line_Left";
        case Position::On_Line_Right: return "On_Line_Right";
        case Position::Off_Line: return "Off_Line";
        case Position::On_Line: return "On_Line";
        case Position::Flag_Left: return "Flag_Left";
        case Position::Flag_Right: return "Flag_Right";
        default: return "Unknown";
    }
}
void debug() {
  Serial.println(leftIRSensor->getValue());
  Serial.println(leftMiddleIRSensor->getValue());
  Serial.println(middleIRSensor->getValue());
  Serial.println(rightMiddleIRSensor->getValue());
  Serial.println(rightIRSensor->getValue());
  Serial.println(positionToString(worldState->getEnemyPosition()));  // prints: LEFT

  Serial.println(leftLineSensor->getValue());
  Serial.println(rightLineSensor->getValue());
  Serial.println(positionToString(worldState->getSelfPosition()));  // prints: LEFT
  // Serial.println(leftMotorDriver->getVelocity());
  // Serial.println(rightMotorDriver->getVelocity());
  delay(100);
}

void memeRight(uint32_t time) {
  robotState->memeRight(time);
}

void memeLeft(uint32_t time) {
  robotState->memeLeft(time);
}

void optimalStrategy(uint32_t time) {
  robotState->optimalStrategy(time);
}

bool isMemeDone() {
  return robotState->isMemeDone();
}

void loop() {
  int dipMode = getDipMode();

  if (digitalRead(START_MODULE)) {
      pollSensors();

      switch (dipMode) {
          case 0:
              //both switches at ON
              
              calculateState(millis());
              break;
          case 1:
              if (!isMemeDone()) {
                  memeRight(millis());
              } else {
                  calculateState(millis());
              }
              break;
          case 2:
              //switch1 at ON, switch2 at 2
              if (!isMemeDone()) {
                  memeLeft(millis());
              } else {
                  calculateState(millis());
              }
              break;
          case 3:
              //both switches at 12
              if (!isMemeDone()) {
                  optimalStrategy(millis());
              } else {
                  calculateState(millis());
              }
              break;

        servo.write(robotState->servo);

      }
  } else {
      robotActions->drive(0, 0);
        robotState->resetMatch();
      servo.write(90);

  }

  updateMotors();
}

 