#ifndef FULLREVERSE_H
#define FULLREVERSE_H

#include "Nodes/Node.h"
#include <Arduino.h>

template<typename T, typename U>
class FullReverse : public BT::Node<T, U> {
public:
    FullReverse(int speed) : BT::Node<T, U>(0, 0), speed(speed){
        
    }

    U Run(T inputs) override {
        U out;
        out.currentLeftMotorPow  = -speed;
        out.currentRightMotorPow = -speed;
        return out;
    }

protected:
    int speed;
};

#endif