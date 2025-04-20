#include "Robot/robotActions.hpp"

RobotActions::RobotActions(MotorDriver *frontLeftDriver, MotorDriver *frontRightDriver, MotorDriver *backLeftDriver, MotorDriver *backRightDriver)
{
    this->frontLeftDriver = frontLeftDriver;
    this->frontRightDriver = frontRightDriver;
    this->backLeftDriver = backLeftDriver;
    this->backRightDriver = backRightDriver;
    this->prev_action = NoneAction;
    this->speed = 0;
}
void RobotActions::Forward(EnemyPositions pos)
{
    // Future Note: Pins set the direction and speed of the robot
    // Value 0 for direction means spin forward and Value 1 for direction means spin backwards
    // Make sure to ramp values for speed to avoid jump
    if (this->prev_action == ForwardAction) {
        this->speed += 2;
        if (this->speed > 100) {
            this->speed = 100;
        }
    } else {
        this->speed = 10;
    }
    frontLeftDriver->setDirection(0);
    frontLeftDriver->setSpeed(this->speed);

    backLeftDriver->setDirection(0);
    backLeftDriver->setSpeed(this->speed);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(this->speed);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(this->speed);

    // Curving towards opp, max turn 85 for slower wheel
    if (pos == MidR) {
        if (this->speed - 15 < 0) {
            frontLeftDriver->setSpeed(0);
            backLeftDriver->setSpeed(0);
        } else {
            frontLeftDriver->setSpeed(this->speed - 15);
            backLeftDriver->setSpeed(this->speed - 15);
        }
    } else if (pos == MidL) {
        if (this->speed - 15 < 0) {
            frontRightDriver->setSpeed(0);
            backRightDriver->setSpeed(0);
        } else {
            frontRightDriver->setSpeed(this->speed - 15);
            backRightDriver->setSpeed(this->speed - 15);
        }
    } 
    this->prev_action = ForwardAction;
}
void RobotActions::Backwards()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(30);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(30);

    frontRightDriver->setDirection(1);
    frontRightDriver->setSpeed(30);

    backRightDriver->setDirection(1);
    backRightDriver->setSpeed(30);
    this->prev_action = BackAction;
}
void RobotActions::Left()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(30);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(30);
    this->prev_action = LeftAction;
}
void RobotActions::Right()
{
    frontLeftDriver->setDirection(1);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(1);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(0);
    frontRightDriver->setSpeed(30);

    backRightDriver->setDirection(0);
    backRightDriver->setSpeed(30);
    this->prev_action = RightAction;
}
void RobotActions::Circle()
{
    frontLeftDriver->setDirection(0);
    frontLeftDriver->setSpeed(10);

    backLeftDriver->setDirection(0);
    backLeftDriver->setSpeed(10);

    frontRightDriver->setDirection(1);
    frontRightDriver->setSpeed(30);

    backRightDriver->setDirection(1);
    backRightDriver->setSpeed(30);
    this->prev_action = CircleAction;
}