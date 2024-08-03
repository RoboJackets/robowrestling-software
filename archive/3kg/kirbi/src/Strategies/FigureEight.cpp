#include "Strategies/FigureEight.h"

FigureEight::FigureEight(int speed, int time2Switch) :
    BT::Node<RobotState, RobotState>(0,0), _speed(speed), _time2Switch(time2Switch)
{
    _lastTime = millis();
}

RobotState FigureEight::Run(RobotState state) {
    if (millis() - _lastTime > _time2Switch) {
        dir = !dir;
        _lastTime = millis();
    }

    RobotState output;
    output.currentRightMotorPow = (dir) ? _speed : 0;
    output.currentLeftMotorPow = (dir) ? 0 : _speed;

    return output;
}
