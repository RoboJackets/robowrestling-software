#include "Robot/robotActions.hpp"

RobotActions::RobotActions(MotorDriver *driver) {
    motorDriver = driver;
}
void RobotActions::Forward() {
    motorDriver->setDirection(0);
    motorDriver->setSpeed(10);
}
void RobotActions::Backwards() {
    motorDriver->setDirection(180);
    motorDriver->setSpeed(10);
}
void RobotActions::Left() {
    motorDriver->setDirection(-90);
    motorDriver->setSpeed(10);
}
void RobotActions::Right() {
    motorDriver->setDirection(90);
    motorDriver->setSpeed(10);
}