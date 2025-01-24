#include "action/robotAction.h"

RobotAction::RobotAction() {
    // initialize empty motor drivers

}

void RobotAction::turnLeft(MotorDriver** motors) {
    // call setDir and setSpeed
    motors[0]->setDir(true);
    motors[1]->setDir(false);
    motors[0]->setSpeed(125);
    motors[1]->setSpeed(125);
}

void RobotAction::turnRight(MotorDriver** motors) {
    // call setDir and setSpeed
    motors[0]->setDir(false);
    motors[1]->setDir(true);
    motors[0]->setSpeed(125);
    motors[1]->setSpeed(125);
}

void RobotAction::go(MotorDriver** motors) {
    // call setDir and setSpeed
    motors[0]->setDir(true);
    motors[1]->setDir(true);
    motors[0]->setSpeed(125);
    motors[1]->setSpeed(125);
}

void RobotAction::GOGOGO(MotorDriver** motors) {
    // call setDir and setSpeed
    motors[0]->setDir(true);
    motors[1]->setDir(true);
    motors[0]->setSpeed(255);
    motors[1]->setSpeed(255);
}

void RobotAction::reverse(MotorDriver** motors) {
    // call setDir and setSpeed
    motors[0]->setDir(false);
    motors[1]->setDir(false);
    motors[0]->setSpeed(125);
    motors[1]->setSpeed(125);
}
