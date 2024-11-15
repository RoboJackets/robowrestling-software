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
}int[] world_state :: line_check() {
    int l_value = line_left -> get_value();
    int r_value = line_right -> get_value();
    int bin = (l_value << 1) + r_value;
    cout << bin;
    return values[bin];
}

int world_state :: enemy_pos() {

}