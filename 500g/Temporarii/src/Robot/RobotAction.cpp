#include "Robot/RobotAction.hpp"

void RobotAction::Forward() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}
void RobotAction::Backwards() {
    motorDriver.setDirection(false);
    motorDriver.setSpeed(-10);
}
void RobotAction::Left() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}
void RobotAction::Right() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}