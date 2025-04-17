#include "action/robotAction.h"

RobotAction::RobotAction(MotorDriver* leftMotorParameter, MotorDriver* rightMotorParameter) {
    // initialize motor drivers to specific values
    leftMotor = leftMotorParameter;
    rightMotor = rightMotorParameter;           
}

void RobotAction::turnLeft() {
    // call setDir and setSpeed
    leftMotor->setDir(0);           // leftMotor is a pointer to an object created in main, so use "->" to set direction. If it was a normal object (not a pointer), use leftMotor.setDir(false)
    rightMotor->setDir(1);
    rightMotor->setSpeed(30);
    leftMotor->setSpeed(120);
}

void RobotAction::turnRight() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(0);
    leftMotor->setSpeed(30);
    rightMotor->setSpeed(120);
}

void RobotAction::go(int weight) {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(1);
    leftMotor->setSpeed(90 + weight);
    rightMotor->setSpeed(90 - weight);
}

void RobotAction::GOGOGO() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(1);
    leftMotor->setSpeed(255);
    rightMotor->setSpeed(255);
}

void RobotAction::reverse() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(0);
    leftMotor->setSpeed(100);
    rightMotor->setSpeed(100);
}

void RobotAction::spinRight() {
    // call setDir and setSpeed
    leftMotor->setDir(1);
    rightMotor->setDir(0);
    leftMotor->setSpeed(60);
    rightMotor->setSpeed(60);
}

void RobotAction::spinLeft() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(1);
    leftMotor->setSpeed(60);
    rightMotor->setSpeed(60);
}

void RobotAction::turnRightSlow() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(0);
    leftMotor->setSpeed(20);
    rightMotor->setSpeed(50);
}

void RobotAction::turnLeftSlow() {
    // call setDir and setSpeed
    leftMotor->setDir(0);
    rightMotor->setDir(0);
    leftMotor->setSpeed(50);
    rightMotor->setSpeed(20);
}
