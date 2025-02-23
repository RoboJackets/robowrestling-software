#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "motor_driver.hpp"
#include "world/world_state.hpp"
#include "robot/robot_state.hpp"
#include "enums/world_enums.hpp"
#include "world/sensors/timer.hpp"

class robot_actions {
    private:
        motor_driver* left_motor;
        motor_driver* right_motor;
    public:
        robot_actions(motor_driver* left_ptr, motor_driver* right_ptr);
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void turn_left(int speed);
        void turn_right(int speed);
        void drive_custom(int LSpeed, int RSpeed, bool LDir, bool RDir);
};

class algorithms {
    private:
        robot_actions* robot;
        world_state* world;
        approach_state app_state;
        timer* thymer;
        bool timer_set;
    public:
        algorithms(robot_actions* robo_actions, world_state* world, timer* thymer);
        void draw();
        int approach_line();
        int forward_safe();
        int turn_towards();
        int dodge();
        void turn_test();
};
#endif