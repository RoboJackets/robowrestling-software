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

    /*
        The if-statement condition checks for the following
        - If either of the two lidars DO NOT read something closer than 150 (cm I think?)
        - If we aren't locked out (lockout is the value of millis() when the lockout was engaged)

        May need to revise the locking out functionality
    */
    if ((state.lidars[2] > 150 || state.lidars[3] > 150) && !(millis() - lockout < LOCKOUT_TIME)) {
        return search->Run(state);
    } else {
        lockout = millis();
    }

    return slam->Run(state);
}
