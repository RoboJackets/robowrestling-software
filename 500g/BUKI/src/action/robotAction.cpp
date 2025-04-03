#include "action/robotAction.h"

RobotAction::RobotAction(MotorDriver* leftMotorParameter, MotorDriver* rightMotorParameter) {
    // initialize motor drivers to specific values
    leftMotor = leftMotorParameter;
    rightMotor = rightMotorParameter;           
}

void RobotAction::turnLeft() {
    // call setDir and setSpeed
    leftMotor->setDir(false);           // leftMotor is a pointer to an object created in main, so use "->" to set direction. If it was a normal object (not a pointer), use leftMotor.setDir(false)
    rightMotor->setDir(true);
    rightMotor->setSpeed(125);
}

void RobotAction::turnRight() {
    // call setDir and setSpeed
    leftMotor->setDir(true);
    rightMotor->setDir(false);
    leftMotor->setSpeed(125);
}

void RobotAction::go() {
    // call setDir and setSpeed
    leftMotor->setDir(true);
    rightMotor->setDir(true);
    leftMotor->setSpeed(125);
    rightMotor->setSpeed(125);
}

void RobotAction::GOGOGO() {
    // call setDir and setSpeed
    leftMotor->setDir(true);
    rightMotor->setDir(true);
    leftMotor->setSpeed(255);
    rightMotor->setSpeed(255);
}

void RobotAction::reverse() {
    // call setDir and setSpeed
    leftMotor->setDir(false);
    rightMotor->setDir(false);
    leftMotor->setSpeed(125);
    rightMotor->setSpeed(125);
}
