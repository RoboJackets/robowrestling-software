#include "Robot/Robot_Actions.hpp"
#include "Robot/World_State.hpp"
#include "Robot/Timer.hpp"
#include "Enums/enemy_states.hpp"
#include "Enums/line_states.hpp"
#include "Enums/algos.hpp"

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

class Algorithms {
    private:
        RobotActions* actions;
        WorldState* world_state;
        Timer* timer;
        line_states self_position;
        enemy_states enemy_position;
        Algos curr_algo;
    public:
        Algorithms(RobotActions* new_action, WorldState* new_state, Timer* timer, line_states self_pos, enemy_states enemy_pos);
        void match_strategy();
        void update_algo_state(line_states self_pos, enemy_states enemy_pos);
        void slammy_whammy();
        void attack_forward();
        void adv_line_movement();
};

#endif // ALGORITHMS_HPP