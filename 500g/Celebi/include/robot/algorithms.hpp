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
        struct action_tracker {
            int times;
            enum movement_states last_func;
        } last_action;
    public:
        robot_actions(motor_driver* left_ptr, motor_driver* right_ptr, timer* time);
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
        int forward_speed;
    public:
        algorithms(robot_actions* robo_actions, world_state* world, timer* thymer);
        void draw();
        int approach_line();
        int forward_safe();
        int turn_towards();
        void back_and_forth();
        int dodge();
        void turn_test();
        void seek_drive(enum enemy_states);
};
#endif