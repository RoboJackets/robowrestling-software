#include <RobotActions.h>
#include <cstdlib>

RobotActions::RobotActions(MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer) {
    leftMotorDriver = leftMotorDriverPointer;
    rightMotorDriver = rightMotorDriverPointer;
}
/* 
Default drive function with left and right speed
- For example, drive(10, 10) would drive forward
- drive(-10, -10) for backward
*/
void RobotActions::drive(int leftSpeed, int rightSpeed) {
    leftMotorDriver -> setSpeed(std::abs(leftSpeed));
    leftMotorDriver -> setDirection(leftSpeed >= 0);
    rightMotorDriver -> setSpeed(std::abs(rightSpeed));
    rightMotorDriver -> setDirection(rightSpeed < 0);
}