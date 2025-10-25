#include "RobotActions.hpp"

RobotActions::RobotActions(MotorDriver* _motorDriver) {
    motorDriver = _motorDriver;
}

void RobotActions::forward(int speed) {
    motorDriver->setSpeed(speed, speed);
    motorDriver->setDirection(FORWARD, FORWARD);
}

void RobotActions::backward(int speed) {
    motorDriver->setSpeed(speed, speed);
    motorDriver->setDirection(BACKWARD, BACKWARD);
}

void RobotActions::turnForward(int leftSpeed, int rightSpeed) {
    motorDriver->setSpeed(leftSpeed, rightSpeed);
    motorDriver->setDirection(FORWARD, FORWARD);
}

void RobotActions::turnBackward(int leftSpeed, int rightSpeed) {
    motorDriver->setSpeed(leftSpeed, rightSpeed);
    motorDriver->setDirection(BACKWARD, BACKWARD);
}

void RobotActions::spinLeft(int speed) {
    motorDriver->setSpeed(speed, speed);
    motorDriver->setDirection(BACKWARD, FORWARD);
}

void RobotActions::spinRight(int speed) {
    motorDriver->setSpeed(speed, speed);
    motorDriver->setDirection(FORWARD, BACKWARD);    
}

void RobotActions::brake() {
    motorDriver->setSpeed(0, 0);
    motorDriver->setSpeed(FORWARD, FORWARD);
}