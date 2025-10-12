#include "world_state.hpp"
#include <Arduino.h>

world_state::world_state(int* lineSensors, int* ir_sensors) {
    this->lineSensors = lineSensors;
    this -> ir_sensors = ir_sensors;
}

void world_state::clean_sensors() {
    for (int i = 0; i < 3; i++) {
        if (ir_sensors[i] == 1) {
            ir_sensors[i] = 0;
            concurrency[i]++;
        }
        else {
            concurrency[i] = 0;
        }
        if (concurrency[i] >= 10) {
            ir_sensors[i] = 1;
        }
    }
}

float* world_state::get_sensors_avg() {
    head++;
    if (head >= buffer_size) {
        head = 0;
    }
    for (int i = 0; i < 3; i++) {
        avgs[i] += static_cast<float>(ir_sensors[i]) / static_cast<float>(buffer_size);
        avgs[i] -= rolling_avgs[i][head]/static_cast<float>(buffer_size);
        rolling_avgs[i][head] = ir_sensors[i];
    }
    return avgs;
}

EnemyPosition world_state::enemy_pos() {
    // simple mapping to your enum values
    // adjust depending on how your IR sensors are arranged
    if (ir_sensors[1] == 1){
        if(ir_sensors[0] == 1 && ir_sensors[2] == 1) return FRONT;
        if (ir_sensors[0] == 1) return MIDLEFT;
        if (ir_sensors[2] == 1) return MIDRIGHT;
        return FARFRONT;
    } 
    if (ir_sensors[0] == 1) return LEFT;
    if (ir_sensors[2] == 1) return RIGHT;
    return NONE;
}

LinePosition world_state::line_check() {
    bool left = lineSensors[0] > 620;
    bool right = lineSensors[1] > 775;

    if (left && right) return CENTER_LINE;
    if (left && !right) return LEFT_LINE;
    if (!left && right) return RIGHT_LINE;
    return OFF_LINE;
}