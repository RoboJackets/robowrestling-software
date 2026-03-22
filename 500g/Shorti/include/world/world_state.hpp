#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "sensors/ir_sensor.hpp"
#include "sensors/line_sensor.hpp"
#include "enums/world_enums.hpp"

#define __ATMEGA__
#include <ustd_array.h>

class world_state {
    private:
        ir_sensor *ir_left;
        ir_sensor *ir_mid_left;
        ir_sensor *ir_mid;
        ir_sensor *ir_mid_right;
        ir_sensor *ir_right;

        line_sensor *line_left;
        line_sensor *line_right;

        line_states line_arr[4] = {OFF, RIGHT_ON, LEFT_ON, BOTH_ON};
        enemy_states enemy_arr[9] = {LEFT, FRONT_LEFT, FRONT, FRONT_RIGHT, RIGHT,
            CLOSE_MID_LEFT, CLOSE_MID, CLOSE_MID_RIGHT, UNKNOWN};
            
    public:
        world_state(line_sensor* line_left, line_sensor* line_right,
            ir_sensor* ir_left, ir_sensor* ir_mid_left, ir_sensor* ir_mid, ir_sensor* ir_mid_right, ir_sensor* ir_right);
        //ustd::array<bool> seen_by_dist_sensors();
        
        line_states line_check();

        enemy_states enemy_pos();
};

#endif