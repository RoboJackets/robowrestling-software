#include "world/world_state.hpp"
// world state processes sensor data and summarizes it
//  ex: turn line sensor data into where our robot is
//  ex: turn ir sensor data into where their robot is
world_state :: world_state(int* line_sensors, int* ir_sensors) {
    this -> line_sensors = line_sensors;
    this -> ir_sensors = ir_sensors;
}

line_states world_state :: line_check() {

    //bit shift the left value and combine with the right value to index into the array
    int bin = ((line_sensors[0] && line_sensors[1]) << 1)
        + (line_sensors[2]&& line_sensors[3]);

    return line_arr[bin];
}

enemy_states world_state :: enemy_pos() {
    bool left_value = ir_sensors[0];
    bool mid_left_value = ir_sensors[1];
    bool mid_value = ir_sensors[2];
    bool mid_right_value = ir_sensors[3];
    bool right_value = ir_sensors[4];

    if (left_value) {
        return LEFT;
    } else if (right_value) {
        return RIGHT;
    } else if (mid_left_value && mid_value && mid_right_value) {
        return CLOSE_MID;
    } else if (mid_left_value && mid_value) {
        return CLOSE_MID_LEFT;
    } else if (mid_right_value && mid_value) {
        return CLOSE_MID_RIGHT;
    } else if (mid_left_value) {
        return FRONT_LEFT;
    } else if (mid_right_value) {
        return FRONT_RIGHT;
    } else if (mid_value) {
        return FRONT;
    }
    return UNKNOWN;
}