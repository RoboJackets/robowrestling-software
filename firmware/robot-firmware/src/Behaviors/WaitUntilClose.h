#ifndef WAIT_UNTIL_CLOSE_H
#define WAIT_UNTIL_CLOSE_H
#include "Behaviors/Nodes/Node.h"

/**
 * Keeps the robot stationary until the enemy robot gets close.
 * Designed for use in the Matador strategy.
 *
 * Note to self: Maybe add paramter to define custom "closeness" value
 * in millimeters
*/
template<typename T, typename U>
class WaitUntilClose : BT::Node<T, U> {
    public:
        WaitUntilClose() : BT::Node<T, U>(0, 0) {

        }

        U Run(T inputs) override {
            this -> _finished = inputs.lidars[2] <= 350 || inputs.lidars[3] <= 350; // test both && and ||

            U out;
            out.currentLeftMotorPow = 0; // We don't need to move, just wait
            out.currentRightMotorPow = 0;
            return out;
        }
};

#endif
