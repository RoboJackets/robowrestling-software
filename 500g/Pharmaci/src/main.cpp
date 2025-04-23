#include <Arduino.h>
#include <IRSensor.h>
#include <LineSensor.h>
#include <MotorDriver.h>
#include <RobotActions.h>
#include <WorldState.h>
#include <RobotState.h>

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

// Shorti Pins
 const int LEFT_IR_90 = 3;
 const int LEFT_IR_45 = 4;
 const int RIGHT_IR_90 = 8;
 const int RIGHT_IR_45 = 6;
 const int MIDDLE_IR = 5;
 const int START_MODULE = 2;
 const int R_POS = 0;
 const int R_NEG = 1;
 const int L_POS = 29;
 const int L_NEG = 28;


 const int LEFT_LINE = A7;
 const int RIGHT_LINE = A6;

void setup() {
  Serial.begin(9600);
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
  robotState = new RobotState(worldState, robotActions);

}


void updateMotors() {



     int leftDirection = leftMotorDriver->getDirection();
     int leftSpeed = leftMotorDriver->getSpeed();
 
     if (leftDirection == 1) {  // if direction is forward
        analogWrite(L_POS, leftSpeed);
        analogWrite(L_NEG, 0);
     } else {                    // if direction is back
        analogWrite(L_POS, 0);
        analogWrite(L_NEG, leftSpeed);
     }
 
     int rightDirection = rightMotorDriver->getDirection();
     int rightSpeed = rightMotorDriver->getSpeed();
 
     if (rightDirection == 1) {  // if direction is forward
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

void calculateState() {
  robotState->calculateState();
}

const char* positionToString(Position pos) {
    switch (pos) {
        case Position::None: return "None";
        case Position::Left: return "Left";
        case Position::Left_Middle: return "Left_Middle";
        case Position::Middle_Close: return "Middle_Close";
        case Position::Middle_Far: return "Middle_Far";
        case Position::Right_Middle: return "Right_Middle";
        case Position::Right: return "Right";
        case Position::On_Line_Left: return "On_Line_Left";
        case Position::On_Line_Right: return "On_Line_Right";
        case Position::Off_Line: return "Off_Line";
        case Position::On_Line: return "On_Line";
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
  delay(1000);
}

void loop() {


  // debug();
  

  if (!digitalRead(START_MODULE)) {
      while(true) {
        robotActions->drive(0, 0);
      }
  } else {
    pollSensors();
      calculateState();
      updateMotors();
  }
}


 