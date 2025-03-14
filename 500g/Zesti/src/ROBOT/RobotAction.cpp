#include "include/ROBOT/RobotAction.h"

void RobotAction::moveForward() {
    move(100, true, 100, true);
}

void RobotAction::moveBackward() {
    move(100, false, 100, false);
}

void RobotAction::turnLeft() {
    move(30, true, 100, true);
}

void RobotAction::turnRight() {
    move(100, true, 30, true);
}

void RobotAction::stop() {
    move(0, true, 0, true);
}

void RobotAction::move(int lMSpeed, bool lMDir, int rMSpeed, bool rMDir) {
    leftMotorDriver.setSpeed(lMSpeed);
    leftMotorDriver.setDirection(lMDir);
    rightMotorDriver.setSpeed(rMSpeed);
    rightMotorDriver.setDirection(rMDir);
}


/**
 * Modified and checked by: Braiden Anderson
 */