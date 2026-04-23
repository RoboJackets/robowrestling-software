#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "robot_actions.hpp"
#include "world/world_state.hpp"
#include "enums/world_enums.hpp"
#include "enums/robot_enums.hpp"
#include "world/timer.hpp"

class algorithms {
    private:
        robot_actions* robot;
        world_state* world;
        timer* draw_timer;
        timer* match_start_timer;
        timer* swerve_timer;
        int* strategy;
        line_states selfPosition;
        enemy_states enemyPosition;
        bool timer_set;
        int forward_speed;
        int turn_direction;
        struct algorithm_states {
            draw_state circle;
            swerve_state swerve;
            attack_state attack;
            match_start match;
        } states;

        struct start_info {
            int powers[4];
            int lengths[4];
        } start_data;
    public:
        algorithms(robot_actions* robo_actions, world_state* world, int* strategy_in, timer* draw_timer, timer *attack_timer, timer *swerve_timer);
        void match_strategy();
        int attack_pattern();
        void seek_drive();
        int draw_circle();
        int attack_forward();
        int turn_towards();
        void test();
        int doge();
        int match_start();
        int draw_circle_edge();
};
#endif