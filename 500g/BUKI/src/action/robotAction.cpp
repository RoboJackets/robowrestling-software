#include "action/robotAction.h"

RobotAction::RobotAction(MotorDriver* leftMotorParameter, MotorDriver* rightMotorParameter) {
    // initialize motor drivers to specific values
    leftMotor = leftMotorParameter;
    rightMotor = rightMotorParameter;           
}

void RobotAction::turnLeft() {
    // call setDir and setSpeed
    leftMotor->setDir(1);           // leftMotor is a pointer to an object created in main, so use "->" to set direction. If it was a normal object (not a pointer), use leftMotor.setDir(false)
    rightMotor->setDir(0);
    rightMotor->setSpeed(125);
    leftMotor->setSpeed(90);
}

void RobotAction::turnRight() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(1);
    leftMotor->setSpeed(125);
    rightMotor->setSpeed(90);
}

void RobotAction::go() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(1);
    leftMotor->setSpeed(125);
    rightMotor->setSpeed(125);
}

void RobotAction::GOGOGO() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(0);
    leftMotor->setSpeed(255);
    rightMotor->setSpeed(255);
}

void RobotAction::reverse() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(1);
    leftMotor->setSpeed(125);
    rightMotor->setSpeed(125);
}
