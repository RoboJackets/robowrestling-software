#include <Arduino.h>
#include "../motor/MotorDriver.h"

#ifndef ROBOT_ACTION_H
#define ROBOT_ACTION_H

class RobotAction {
    private:
        MotorDriver MotorDriver;
    
    public:
        void move_forwards();
        void move_backwards();
        void turn_left();
        void turn_right();

};


#endif