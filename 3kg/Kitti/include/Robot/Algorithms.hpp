#include "Robot/Robot_Actions.hpp"
#include "Robot/World_State.hpp"
#include "Enums/enemy_states.hpp"
#include "Enums/line_states.hpp"

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

class Algorithms {
    private:
        RobotActions* actions;
        WorldState* world_state;
        line_states self_position;
        enemy_states enemy_position;
    public:
        Algorithms(RobotActions* new_action, WorldState* new_state, line_states self_pos, enemy_states enemy_pos);
        void match_strategy();
        void slammy_whammy();
        void attack_forward();
};

#endif // ALGORITHMS_HPP