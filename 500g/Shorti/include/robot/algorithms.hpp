#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "motor_driver.hpp"
#include "world/world_state.hpp"
#include "robot/robot_state.hpp"
#include "enums/world_enums.hpp"
#include "enums/robot_enums.hpp"
#include "world/sensors/timer.hpp"

class robot_actions {
    private:
        motor_driver* left_motor;
        motor_driver* right_motor;
        timer* time;
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
        timer* thymer;
        bool timer_set;
        int forward_speed;
        struct algorithm_states {
            draw_state circle;
            swerve_state swerve;
        } states;

    public:
        algorithms(robot_actions* robo_actions, world_state* world, timer* thymer);
        int draw_circle();
        int attack_forward();
        int turn_towards();
        int dodge();
        void seek_drive();
        int swerve();
        void brake();
};
#endif