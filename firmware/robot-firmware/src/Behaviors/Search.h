#ifndef SEARCH_H
#define SEARCH_H

#include "Nodes/Node.h"
#include "MotorController/MotorController.h"

template<typename T, typename U>
class Search : public BT::Node<T, U> {
public:
    enum State {
        SEARCH,
        TURN_LEFT,
        TURN_RIGHT
    }

    Search(int turnSpeed) : turnSpeed(turnSpeed), state(SEARCH){
        
    }

    U Run(T inputs) override {
        _finished = inputs.lidar[2] < 1000 && inputs.lidars[3] < 1000; // both lidars see something

        U out;
        switch (state) {
        case SEARCH:
            out.motor1 = turnSpeed;
            out.motor2 = -turnSpeed;
        }
        case TURN_LEFT:
            out.motor1 = -turnSpeed;
            out.motor2 = turnSpeed;
        case TURN_RIGHT:
            out.motor1 = turnSpeed;
            out.motor2 = -turnSpeed;
        return out;
    }

    void updateState(T inputs) {
        int minLidar = 1000;
        int minLidarIndex = -1;
        for (int i = 0; i < inputs.lidar.size(); i++) {
            if (inputs.lidar[i] < minLidar) {
                minLidar = inputs.lidar[i];
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