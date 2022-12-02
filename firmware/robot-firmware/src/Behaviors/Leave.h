#ifndef LEAVE_H
#define LEAVE_H
#include <Arduino.h>
#include "Behaviors/Nodes/Node.h"

/**
 * Moves the robot out of the way of the enemy robot by turning and moving it
 * backwards.
 * Designed for use in the Matador strategy.
 *
 * Note to self: Perhaps find a way to utilize a line sensor to strafe around
 * the edge of the Dohyo
*/
template<typename T, typename U>
class Leave : BT::Node<T, U> {
    public:
        Leave(long startTime) : BT::Node<T, U>(0, 0), _startTime(startTime) {

        }

        U Run(T inputs) override {
            long currMillis = millis();
            this -> _finished = currMillis - _startTime >= 500;

            U out;
            out.currentLeftMotorPow = -0.5; // Turn and move back at the same time
            out.currentRightMotorPow = -1;
            return out;
        }

    protected:
        long _startTime;
};

#endif

