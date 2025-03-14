#include "../include/actions/robot_action.h"


//PLACE HOLDER VALUES UNTIL WE CAN TEST HOW MUCH IT ACTUALLY BE DOING TYPE SHITTTTTTTTTT
//Working under assumptions that 1 means forward and 0 means backwards for direction

// FORWARD
RobotAction::RobotAction(MotorDriver *left, MotorDriver *right){
    this->leftMotorDriver = left;
    this -> rightMotorDriver = right;

}
void RobotAction::smallForward() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(1);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(1);
}
void RobotAction::medForward() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(128);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(128);
}
void RobotAction::largeForward() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(3);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(3);
}

// BACKWARD
void RobotAction::smallBack() {
    leftMotorDriver -> setDirection(0);
    leftMotorDriver -> setSpeed(1);
    rightMotorDriver -> setDirection(0);
    rightMotorDriver -> setSpeed(1);
}
void RobotAction::medBack() {
    leftMotorDriver -> setDirection(0);
    leftMotorDriver -> setSpeed(2);
    rightMotorDriver -> setDirection(0);
    rightMotorDriver -> setSpeed(2);
}
void RobotAction::largeBack() {
    leftMotorDriver -> setDirection(0);
    leftMotorDriver -> setSpeed(3);
    rightMotorDriver -> setDirection(0);
    rightMotorDriver -> setSpeed(3);
}

// LEFT
void RobotAction::smallLeft() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(1);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(2);
}
void RobotAction::medLeft() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(1);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(3);
}
void RobotAction::largeLeft() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(1);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(4);
}

// RIGHT
void RobotAction::smallRight() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(2);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(1);
}
void RobotAction::medRight() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(3);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(1);
}
void RobotAction::largeRight() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(4);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(1);
}

// STOP

void RobotAction::stop() {
    leftMotorDriver -> setDirection(1);
    leftMotorDriver -> setSpeed(0);
    rightMotorDriver -> setDirection(1);
    rightMotorDriver -> setSpeed(0);
}