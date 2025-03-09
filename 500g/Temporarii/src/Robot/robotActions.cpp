#include "Robot/robotActions.hpp"

RobotActions::RobotActions(MotorDriver *frontLeftDriver, MotorDriver *frontRightDriver, MotorDriver *backLeftDriver, MotorDriver *backRightDriver)
{
    this->frontLeftDriver = frontLeftDriver;
    this->frontRightDriver = frontRightDriver;
    this->backLeftDriver = backLeftDriver;
    this->backRightDriver = backRightDriver;
}
void RobotActions::Forward()
{
    // Future Note: Pins set the direction and speed of the robot
    // Value 0 for direction means spin forward and Value 1 for direction means spin backwards
    frontLeftDriver->setDirection(0);
    frontLeftDriver->setSpeed(100);

    backLeftDriver->setDirection(0);
    backLeftDriver->setSpeed(100);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(100);
}
void RobotActions::Backwards()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(100);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(100);

    frontRightDriver->setDirection(1);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(1);
    backRightDriver->setSpeed(100);
}
void RobotActions::Left()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(100);
}
void RobotActions::Right()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(100);
}
void RobotActions::Circle()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(100);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(100);
}