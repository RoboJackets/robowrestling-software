#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "robot_actions.hpp"
#include "world/world_state.hpp"
#include "enums/world_enums.hpp"
#include "enums/robot_enums.hpp"
#include "world/timer.hpp"
#include <algorithm>

class algorithms {
    private:
        robot_actions* robot;
        world_state* world;
        timer* draw_timer;
        timer* attack_timer;
        line_states selfPosition;
        enemy_states enemyPosition;
        bool timer_set;
        int forward_speed;
        struct algorithm_states {
            draw_state circle;
            swerve_state swerve;
            attack_state attack;
        } states;

    public:
        algorithms(robot_actions* robo_actions, world_state* world, timer* draw_timer, timer *attack_timer);
        void match_strategy();
        void slammy_whammy();
        void draw_seek();
        void seek();
        int draw_circle();
        int attack_forward();
        int turn_towards();
        int attack_forward_no_delay();
        int turn_towards_no_delay();
        int dodge();
        void seek_drive();
        int swerve();
        void test();
};
#endif