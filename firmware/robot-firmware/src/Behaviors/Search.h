#ifndef SEARCH_H
#define SEARCH_H

#include "Nodes/Node.h"

template<typename T, typename U>
class Search : public BT::Node<T, U> {
public:
    enum State {
        SEARCH,
        TURN_LEFT,
        TURN_RIGHT
    };

    Search(int turnSpeed) : BT::Node<T, U>(0, 0), turnSpeed(turnSpeed), state(SEARCH) {
        
    }

    U Run(T inputs) override {
        this->_finished = inputs.lidars[2] < 1000 && inputs.lidars[3] < 1000; // both lidars see something

        updateState(inputs);

        U out;
        switch (state) {
        case SEARCH:
            out.currentLeftMotorPow  = turnSpeed;
            out.currentRightMotorPow = -turnSpeed;
            break;
        case TURN_LEFT:
            out.currentLeftMotorPow  = -turnSpeed;
            out.currentRightMotorPow = turnSpeed;
            break;
        case TURN_RIGHT:
            out.currentLeftMotorPow = turnSpeed;
            out.currentRightMotorPow = -turnSpeed;
            break;
        }
        return out;
    }

    void updateState(T inputs) {
        uint32_t minLidar = 1000;
        int minLidarIndex = -1;
        for (int i = 0; i < 6; i++) {
            if (inputs.lidars[i] < minLidar) {
                minLidar = inputs.lidars[i];
                minLidarIndex = i;
            }
        }
        if (0 <= minLidarIndex && minLidarIndex <= 2) {
            state = TURN_LEFT;
        }
        else if (minLidarIndex >= 3) {
            state = TURN_RIGHT;
        } else {
            state = SEARCH;
        }
    }

protected:
    int turnSpeed;
    State state;
};

#endif