#include "Robot/RobotAction.h"

void RobotActions::Forward() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}
void RobotActions::Backwards() {
    motorDriver.setDirection(false);
    motorDriver.setSpeed(-10);
}
void RobotActions::Left() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}
void RobotActions::Right() {
    motorDriver.setDirection(true);
    motorDriver.setSpeed(10);
}