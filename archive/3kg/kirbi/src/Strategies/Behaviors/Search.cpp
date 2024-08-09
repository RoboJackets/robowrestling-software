#include "Strategies/Behaviors/Search.h"

Search::Search(int turnSpeed) : BT::Node<RobotState, RobotState>(0, 0), turnSpeed(turnSpeed), state(SEARCH) {}

RobotState Search::Run(RobotState inputs) {
    this->_finished = inputs.lidars[2] < 150 && inputs.lidars[3] < 150; // both lidars see something

    updateState(inputs);

    RobotState out;
    out.currentLeftMotorPow  = turnSpeed;
    out.currentRightMotorPow = -turnSpeed;
    return out;
}

void Search::updateState(RobotState inputs) {
    uint32_t minLidar = 1000;
    int minLidarIndex = -1;
    for (int i = 0; i < 6; i++) {
        if (inputs.lidars[i] < minLidar) {
            minLidar = inputs.lidars[i];
            minLidarIndex = i;
        }
    }
    state = SEARCH;
}
