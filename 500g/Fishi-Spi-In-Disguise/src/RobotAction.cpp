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
    setIsBraking(false);
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::forward(int _speed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(_speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(_speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::back() {
    setIsBraking(false);
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::back(int _speed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(_speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(_speed);
    rightMotorDriver->setDirection(0);
}

/**
 * slow fast for left
 * fast slow for right
 */
void RobotAction::turn(int leftSpeed, int rightSpeed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(leftSpeed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(rightSpeed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::turnBack(int leftSpeed, int rightSpeed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(leftSpeed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(rightSpeed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::brake() {
    setIsBraking(true);
    leftMotorDriver->setSpeed(0);
    rightMotorDriver->setSpeed(0);
}

void RobotAction::pivotLeft() {
    setIsBraking(false);
    leftMotorDriver->setSpeed(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::pivotRight() {
    setIsBraking(false);
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(0);
}

void RobotAction::spinLeft(int _speed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(_speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(_speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::spinRight(int _speed) {
    setIsBraking(false);
    leftMotorDriver->setSpeed(_speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(_speed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::spinLeft() {
    setIsBraking(false);
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(0);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(1);
}

void RobotAction::spinRight() {
    setIsBraking(false);
    leftMotorDriver->setSpeed(speed);
    leftMotorDriver->setDirection(1);
    rightMotorDriver->setSpeed(speed);
    rightMotorDriver->setDirection(0);
}

void RobotAction::setIsBraking(bool isBraking) {
    leftMotorDriver->setIsBraking(isBraking);
    rightMotorDriver->setIsBraking(isBraking);
}