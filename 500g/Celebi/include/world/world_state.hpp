#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "sensors/ir_sensor.hpp"
#include "sensors/line_sensor.hpp"
#include "enums/world_enums.hpp"
#include <array>

class world_state {
    private:
        ir_sensor *ir_left;
        ir_sensor *ir_mid_left;
        ir_sensor *ir_mid;
        ir_sensor *ir_mid_right;
        ir_sensor *ir_right;

        line_sensor *line_left;
        line_sensor *line_right;

        line_states line_values[4] = {OFF, RIGHT_ON, LEFT_ON, BOTH_ON};
    
    public:
        world_state(line_sensor* line_left, line_sensor* line_right,
            ir_sensor* ir_left, ir_sensor* ir_mid_left, ir_sensor* ir_mid, ir_sensor* ir_mid_right, ir_sensor* ir_right);
        std::array<bool, 5> seen_by_dist_sensors();
        
        line_states line_check();

        int enemy_pos();
};

#endif