#include "world/world_state.hpp"
// world state processes sensor data and summarizes it
//  ex: turn line sensor data into where our robot is
//  ex: turn ir sensor data into where their robot is
world_state :: world_state(bool* line_sensors, bool* ir_sensors) {
    this->line_sensors = line_sensors;
    this->ir_sensors = ir_sensors;
}

line_states world_state :: line_check() {

    //bit shift the left value and combine with the right value to index into the array
    uint8_t bin = (line_sensors[0] << 1) + (line_sensors[1]);

    return line_arr[bin];
}

enemy_states world_state :: enemy_pos() {
    bool left_value = ir_sensors[0];
    bool mid_left_value = ir_sensors[1];
    bool mid_value = ir_sensors[2];
    bool mid_right_value = ir_sensors[3];
    bool right_value = ir_sensors[4];
    // right, mid_right, mid, mid_left, left

    if (left_value) {
        //x,x,x,0,1
        return LEFT;
    } else if (right_value) {
        //1,0,x,x,x
        return RIGHT;
    } else if (mid_left_value && mid_value && mid_right_value) {
        //x,1,1,1,x
        return CLOSE_MID;
    } else if (mid_left_value && mid_value) {
        //0,1,1,0,0
        return CLOSE_MID_LEFT;
    } else if (mid_right_value && mid_value) {
        //0,0,1,1,0
        return CLOSE_MID_RIGHT;
    } else if (mid_left_value) {
        //x,x,0,1,1
        return FRONT_LEFT;
    } else if (mid_right_value) {
        //0,0,0,1,1
        return FRONT_RIGHT;
    } else if (mid_value) {
        //0,0,1,0,0
        return FRONT;
    }
    //0,0,0,0,0
    return UNKNOWN;
}