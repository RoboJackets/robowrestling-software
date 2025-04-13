#include <Arduino.h>
#include "../motor/MotorDriver.h"

#ifndef ROBOT_ACTION_H
#define ROBOT_ACTION_H

class RobotAction {
    private:
        MotorDriver *leftMotorDriver;
        MotorDriver *rightMotorDriver;
     /*voltage will either be 0 or 3.3+ for the direction pin when moving forward/backward, for pwn, voltage is between 0 - 3.3 , for forward, write 0 to the direction pin*/
    public:
        void move_forwards();
        void move_backwards();
        void turn_left();
        void turn_right();

};


#endif