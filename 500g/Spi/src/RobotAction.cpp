#include "RobotAction.h"

RobotAction::RobotAction(MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer, int speedValue) {
    leftMotorDriver = leftMotorDriverPointer;
    rightMotorDriver = rightMotorDriverPointer;
    speed = speedValue;
}

void RobotAction::setSpeed(int speedValue) {
    speed = speedValue;
}

void RobotAction::forward() {
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::back() {
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::brake() {
    leftMotorDriver->setSpeed(0);
    rightMotorDriver->setSpeed(0);
}

void RobotAction::pivotLeft() {
    leftMotorDriver->setSpeed(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::pivotRight() {
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(0);
}

void RobotAction::spinLeft() {
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::spinRight() {
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::slightTurnLeft() {
    leftMotorDriver->setSpeed(speed - 20);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}