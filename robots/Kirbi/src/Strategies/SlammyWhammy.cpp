#include "Strategies/SlammyWhammy.h"

SlammyWhammy::SlammyWhammy(int turnSpeed, int slamSpeed) : BT::Node<RobotState, RobotState>(0, 0) {
    search = new Search(turnSpeed);
    slam = new Slam(slamSpeed);
}


RobotState SlammyWhammy::Run(RobotState state) {
    // U out;
    // out.currentLeftMotorPow = 0;
    // out.currentRightMotorPow = 0;
    // if (state.lidars[2] > 150 || state.lidars[3] > 150) {
    //     return out;
    // }

    if ((state.lidars[2] > 150 || state.lidars[3] > 150) && !(millis() - lockout < LOCKOUT_TIME)) {
        return search->Run(state);
    } else {
        lockout = millis();
    }

    return slam->Run(state);
}
