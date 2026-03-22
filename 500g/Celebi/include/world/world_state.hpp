#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "enums/world_enums.hpp"

class world_state {
    private:
        int* line_sensors;
        int* ir_sensors;
        line_states line_arr[4] = {OFF, RIGHT_ON, LEFT_ON, BOTH_ON};
            
    public:
        world_state(int line_sensors[], int ir_sensors[]);
        
        line_states line_check();

        enemy_states enemy_pos();
};

#endif