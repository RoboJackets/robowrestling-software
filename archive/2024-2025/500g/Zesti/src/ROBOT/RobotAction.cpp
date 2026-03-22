#include "Zesti/include/ROBOT/RobotAction.h"

void RobotAction::moveForward() {
    leftMotorDriver.setSpeed(100);
    leftMotorDriver.setDirection(true);
    rightMotorDriver.setSpeed(100);
    rightMotorDriver.setDirection(true);
}

void RobotAction::moveBackward() {
    leftMotorDriver.setSpeed(100);
    leftMotorDriver.setDirection(false);
    rightMotorDriver.setSpeed(100);
    rightMotorDriver.setDirection(false);
}

void RobotAction::turnLeft() {
    leftMotorDriver.setSpeed(30);
    leftMotorDriver.setDirection(true);
    rightMotorDriver.setSpeed(100);
    rightMotorDriver.setDirection(true);
}

void RobotAction::turnRight() {
    leftMotorDriver.setSpeed(100);
    leftMotorDriver.setDirection(true);
    rightMotorDriver.setSpeed(30);
    rightMotorDriver.setDirection(true);
}

void RobotAction::stop() {
    leftMotorDriver.setSpeed(0);
    leftMotorDriver.setDirection(true);
    rightMotorDriver.setSpeed(0);
    rightMotorDriver.setDirection(true);
}