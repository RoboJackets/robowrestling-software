#include "Brazil.h"

Brazil::Brazil(int speed) : BT::Node<RobotState, RobotState>(0, 0),
    _speed(speed),
    _turnStartMillis(0),
    _hasHitEdge(false) {}

RobotState Brazil::Run(RobotState state) {
    RobotState output = state;

    if (_hasHitEdge || state.atBounds) {
        if (!_hasHitEdge) {
            // Just hit bounds
            _turnStartMillis = millis();
        }

        // do the shuffle
        int timeSpentTurning = millis() - _turnStartMillis;
        _hasHitEdge = timeSpentTurning < BRAZIL_TURN_MILLIS;

        output.currentLeftMotorPow = -_speed;
        output.currentRightMotorPow = _speed;
    } else {
        output.currentLeftMotorPow = _speed;
        output.currentRightMotorPow = _speed;
    }

    return output;
}
