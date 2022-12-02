#ifndef WAIT_UNTIL_CLOSE_H
#define WAIT_UNTIL_CLOSE_H
#include "Behaviors/Nodes/Node.h"

template<typename T, typename U>
class WaitUntilClose : BT::Node<T, U> {
    public:
        WaitUntilClose() : BT::Node<T, U>(0, 0) {

        }

        U Run(T inputs) override {
            this -> _finished = inputs.lidars[2] <= 350 && inputs.lidars[3] <= 350;

            U out;
            out.motor1 = 0; // We don't need to move, just wait
            out.motor2 = 0;
            return out;
        }
};

#endif
