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
    rightMotor->setSpeed(90);
    leftMotor->setSpeed(90);
}

void RobotAction::turnRight() {
    // call setDir and setSpeed
    leftMotor->setDir(true);
    rightMotor->setDir(false);
    leftMotor->setSpeed(90);
    rightMotor->setSpeed(90);
}

void RobotAction::go() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(1);
    leftMotor->setSpeed(75);
    rightMotor->setSpeed(75);
}

void RobotAction::GOGOGO() {
    // call setDir and setSpeed
    leftMotor->setDir(true);
    rightMotor->setDir(true);
    leftMotor->setSpeed(200);
    rightMotor->setSpeed(200);
}

void RobotAction::reverse() {
    // call setDir and setSpeed
    leftMotor->setDir(false);
    rightMotor->setDir(false);
    leftMotor->setSpeed(90);
    rightMotor->setSpeed(90);
}

void RobotAction::spinRight() {
    leftMotor->setDir(false);
    rightMotor->setDir(true);
    leftMotor->setSpeed(90);
    rightMotor->setSpeed(90);
}

void RobotAction::spinLeft() {
    leftMotor->setDir(true);
    rightMotor->setDir(false);
    leftMotor->setSpeed(60);
    rightMotor->setSpeed(60);
}

void RobotAction::reverseLeft() {
    // call setDir and setSpeed
    leftMotor->setDir(false);
    rightMotor->setDir(false);
    leftMotor->setSpeed(30);
    rightMotor->setSpeed(200);
}

void RobotAction::reverseRight() {
    // call setDir and setSpeed
    leftMotor->setDir(false);
    rightMotor->setDir(false);
    leftMotor->setSpeed(200);
    rightMotor->setSpeed(30);
}