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

    Search(int speed) : speed(speed){
        
    }

    U Run(T inputs) override {
        _finished = false; // neither lidars see anything

        U out;
        out.motor1 = 0;
        out.motor2 = 0;
        return out;
    }

protected:
    int speed;
};

#endif