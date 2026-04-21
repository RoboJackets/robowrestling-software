#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "robot_actions.hpp"
#include "world/world_state.hpp"
#include "enums/world_enums.hpp"
#include "enums/robot_enums.hpp"
#include "world/timer.hpp"
#include "types.hpp"
#include "const.hpp"
#include <Arduino.h>
#include <stdint.h>

class algorithms {
    private:
        robot_actions* robot;
        world_state* world;
        timer* draw_timer;
        timer* match_start_timer;
        uint8_t* strategy;
        line_states selfPosition;
        enemy_states enemyPosition;
        struct algorithm_states {
            draw_state circle;
            swerve_state swerve;
            attack_state attack;
            match_start match;
        } states;
#ifdef PROFILING
        algorithm_stats* algo_stats;
#endif
    public:
        algorithms(robot_actions* robo_actions, world_state* world, uint8_t* strategy_in, timer* draw_timer, timer *attack_timer);
        void match_strategy();
        
        int match_start();

        int attack_pattern();
        int draw_circle();
        int attack_forward();
        int turn_towards();
#ifdef PROFILING
        void add_stats(algorithm_stats* algo_stats);
#endif
        void test();

        int draw_circle_edge();
};
#endif