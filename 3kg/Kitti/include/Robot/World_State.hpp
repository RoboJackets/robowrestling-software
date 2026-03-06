#include "Enums/line_states.hpp"
#include "Enums/enemy_states.hpp"

#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

// World state representation
class WorldState {
    private:
        int line_sensors[4];
        int ir_sensors[7];
    public:
        WorldState(int line[4], int ir[7]);
        void update_sensors(int line[4], int ir[7]);
        line_states line_check();
        enemy_states enemy_pos();
};

#endif // WORLD_STATE_HPP