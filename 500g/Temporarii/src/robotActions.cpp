#include "robotActions.hpp"
#include "motorDriver.hpp"

// type | Class Name | function name
bool RobotActions::getLeftSpeed() {
    return leftWheelSpeed;
}
bool RobotActions::getRightSpeed() {
    return rightWheelSpeed;
}
void RobotActions::stopRobot() {
    leftWheelSpeed = 0;
    rightWheelSpeed = 0;
}