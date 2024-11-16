#include "robot/RobotActions.h"
//double array/degree implementation
RobotActions :: RobotActions(MotorDriver* leftPtr, MotorDriver* rightPtr){
    leftMotor = leftPtr;
    rightMotor = rightPtr;
}

void RobotActions :: brake() {
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
}

void RobotActions :: driveForward(int speed) {
    //motorDriver implmentation
}

void RobotActions :: driveBackward(int speed) {
    //motorDriver implmentation
}

void RobotActions :: turnLeft(int speed) {
    //motorDriver implmentation
}

void RobotActions :: turnRight(int speed) {
    //motorDriver implmentation
}