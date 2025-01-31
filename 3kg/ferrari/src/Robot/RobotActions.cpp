#include "robot/RobotActions.h"

RobotActions :: RobotActions(){
    motorDriver = MotorDriver::getInstance()->getMotorDriver();
}

void RobotActions :: brake() {
    motorDriver->ForwardM1(address, 0);
    motorDriver->ForwardM2(address, 0);
}

void RobotActions :: driveForward() {
    motorDriver->ForwardM1(address, 127);
    motorDriver->ForwardM2(address, 127);
}

void RobotActions :: driveForward(int speed) {
    motorDriver->ForwardM1(address, speed);
    motorDriver->ForwardM2(address, speed);
}

void RobotActions :: driveBackward() {
    motorDriver->BackwardM1(address, 127);
    motorDriver->BackwardM2(address, 127);
}

void RobotActions :: driveBackward(int speed) {
    motorDriver->BackwardM1(address, speed);
    motorDriver->BackwardM2(address, speed);
}

void RobotActions :: spinLeft() { // idk if this is true, we may need to switch values but for now we can go with it
    motorDriver->ForwardM1(address, 127);
    motorDriver->BackwardM2(address, 127);
}

void RobotActions :: spinRight() {
    motorDriver->BackwardM1(address, 127);
    motorDriver->ForwardM2(address, 127);
}

void RobotActions :: spinLeft(int speed) {
    motorDriver->ForwardM1(address, speed);
    motorDriver->BackwardM2(address, speed);
}

void RobotActions :: spinRight(int speed) {
    motorDriver->BackwardM1(address, speed);
    motorDriver->ForwardM2(address, speed);
}

void RobotActions :: turnRight(int turnRadius) {

}

void RobotActions :: turnLeft(int turnRadius) {

}