#ifndef SLAM_H
#define SLAM_H

#include "Nodes/Node.h"
#include "MotorController/MotorController.h"

template<typename T, typename U>
class Slam : public BT::Node<T, U> {
public:
    Slam(int speed) : speed(speed){
        
    }

    U Run(T inputs) override {
        _finished = inputs.lidar1 > 1000 & inputs.lidars2 > 1000; // neither lidars see anything

        U out;
        out.motor1 = speed;
        out.motor2 = speed;
        return out;
    }

protected:
    int speed;
};

#endif