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
        _finished = inputs.lidar1 > 1000 & inputs.lidars2 > 1000;

        U out;
        if (inputs.lidar1 > 10) {
            out.motor1 = 10;
            out.motor2 = 10;
        } else {
            out.motor1 = 0;
            out.motor2 = 0;
        }
        return out;
    }

protected:
    int speed;
};

#endif