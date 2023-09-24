#ifndef SLAM_H
#define SLAM_H

#include "Nodes/Node.h"
#include <Arduino.h>

template<typename T, typename U>
class Slam : public BT::Node<T, U> {
public:
    Slam(int speed) : BT::Node<T, U>(0, 0), speed(speed){

    }

    U Run(T inputs) override {
        this->_finished = inputs.lidars[2] > 150 || inputs.lidars[3] > 150; // neither lidars see anything
        U out;
        out.currentLeftMotorPow  = speed-20;
        out.currentRightMotorPow = speed;
        return out;
    }

protected:
    int speed;
};

#endif
