#include "world/world_state.hpp"
// world state processes sensor data and summarizes it
//  ex: turn line sensor data into where our robot is
//  ex: turn ir sensor data into where their robot is
world_state :: world_state(line_sensor* line_left, line_sensor* line_right,
    ir_sensor* ir_left, ir_sensor* ir_mid_left, ir_sensor* ir_mid, ir_sensor* ir_mid_right, ir_sensor* ir_right) {
    this -> ir_left = ir_left;
    this -> ir_mid_left = ir_mid_left;
    this -> ir_mid = ir_mid;
    this -> ir_mid_right = ir_mid_right;
    this -> ir_right = ir_right;

    this -> line_left = line_left;
    this -> line_right = line_right;
}

line_states world_state :: line_check() {
    int l_value = line_left -> get_value();
    int r_value = line_right -> get_value();

    //bit shift the left value and combine with the right value to index into the array
    //if both = 0, bin = 0
    //if r_value  = 1, bin = 1
    //if l_value = 1, bin = 2
    //if both = 1, bin = 3
    int bin = (l_value << 1) + r_value;

    return line_arr[bin];
}

int world_state :: enemy_pos() {
    bool left_value = ir_left -> get_ir_sense();
    bool mid_left_value = ir_mid_left -> get_ir_sense();
    bool mid_value = ir_mid -> get_ir_sense();
    bool mid_right_value = ir_mid_right -> get_ir_sense();
    bool right_value = ir_right -> get_ir_sense();

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