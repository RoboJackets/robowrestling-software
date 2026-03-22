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
    //if both are black, bin = 0
    //if just right is black, bin = 1
    //if just left is black, bin = 2
    //if both are white, bin = 3
    int left_on = l_value < 40 ? 1 : 0;
    int right_on = r_value < 40 ? 1 : 0;
    int bin = ((left_on) << 1) + right_on;

    return line_arr[bin];
}

enemy_states world_state :: enemy_pos() {
    bool left_value = ir_left -> get_ir_sensor();
    bool mid_left_value = ir_mid_left -> get_ir_sensor();
    bool mid_value = ir_mid -> get_ir_sensor();
    bool mid_right_value = ir_mid_right -> get_ir_sensor();
    bool right_value = ir_right -> get_ir_sensor();

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