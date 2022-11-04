#ifndef SLAM_H
#define SLAM_H

#include "Nodes/Node.h"
#include "MotorController/MotorController.h"

template<typename T, typename U>
class Slam : public BT::Node<T, U> {
public:
    Slam(int speed) : speed(speed){
        
    }

    T Run() override {

    }

protected:
    int speed;
};

#endif