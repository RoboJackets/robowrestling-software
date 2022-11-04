#ifndef SLAM_H
#define SLAM_H

#include "Nodes/Node.h"
#include "MotorController/MotorController.h"

template<typename T>
class Slam : public BT::Node<T> {
public:
    Slam(int speed) : speed(speed){
        
    }

    T Run() override {

    }

protected:
    int speed;
};

#endif