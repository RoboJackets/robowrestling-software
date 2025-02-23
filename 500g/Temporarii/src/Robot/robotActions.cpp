#include "Robot/robotActions.hpp"

RobotActions::RobotActions(MotorDriver *frontLeftDriver, MotorDriver *frontRightDriver, MotorDriver *backLeftDriver, MotorDriver *backRightDriver) {
    this->frontLeftDriver = frontLeftDriver;
    this->frontRightDriver = frontRightDriver;
    this->backLeftDriver = backLeftDriver;
    this->backRightDriver = backRightDriver;
}
void RobotActions::Forward() {
    frontLeftDriver->setDirection(0);
    frontLeftDriver->setSpeed(100);

    backLeftDriver->setDirection(0);
    backLeftDriver->setSpeed(100);
    
    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(100);
}
void RobotActions::Backwards() {
    frontLeftDriver->setDirection(180);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(180);
    backLeftDriver->setSpeed(10);
    
    frontRightDriver->setDirection(180);
    frontRightDriver->setSpeed(10);

    backRightDriver->setDirection(180);
    backRightDriver->setSpeed(10);
}
void RobotActions::Left() {
    frontLeftDriver->setDirection(-90);
    frontLeftDriver->setSpeed(-10);
    
    backLeftDriver->setDirection(-90);
    backLeftDriver->setSpeed(-10);

    frontRightDriver->setDirection(-90);
    frontRightDriver->setSpeed(10);

    backRightDriver->setDirection(-90);
    backRightDriver->setSpeed(10);
}
void RobotActions::Right() {
    frontLeftDriver->setDirection(90);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(90);
    backLeftDriver->setSpeed(10);
    
    frontRightDriver->setDirection(90);
    frontRightDriver->setSpeed(-10);

    backRightDriver->setDirection(90);
    backRightDriver->setSpeed(-10);
}