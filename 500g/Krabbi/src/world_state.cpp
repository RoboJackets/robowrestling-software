#include "world_state.hpp"
#include <Arduino.h>

world_state::world_state(int* lineSensors, int* ir_sensors) {
    this->lineSensors = lineSensors;
    this -> ir_sensors = ir_sensors;
}

// void world_state::clean_sensors() {
//     for (int i = 0; i < 5; i++) {
//         if (ir_sensors[i] == 1) {
//             ir_sensors[i] = 0;
//             concurrency[i]++;
//         }
//         else {
//             concurrency[i] = 0;
//         }
//         if (concurrency[i] >= 10) {
//             ir_sensors[i] = 1;
//         }
//     }
// }

float* world_state::get_sensors_avg() {
    head++;
    if (head >= buffer_size) {
        head = 0;
    }
    for (int i = 0; i < 5; i++) { //changed to 5 for 5 sensors
        avgs[i] += static_cast<float>(ir_sensors[i]) / static_cast<float>(buffer_size);
        avgs[i] -= rolling_avgs[i][head]/static_cast<float>(buffer_size);
        rolling_avgs[i][head] = ir_sensors[i];
    }
    return avgs;
}

EnemyPosition world_state::enemy_pos() {
    // simple mapping to your enum values
    // adjust depending on how your IR sensors are arranged
    if (avgs[2] >= 0.9){
        if(avgs[1] >= 0.9 && avgs[3] >= 0.9) return FRONT;
        if (avgs[1] >= 0.9) return MIDLEFT;
        if (avgs[3] >= 0.9) return MIDRIGHT;
        return FARFRONT;
    }
    if (avgs[1] >= 0.9) return MIDLEFT;
    if (avgs[3] >= 0.9) return MIDRIGHT;
    if (avgs[0] >= 0.9) return LEFT;
    if (avgs[4] >= 0.9) return RIGHT;
    return NONE;
}

LinePosition world_state::line_check() {
    bool left = lineSensors[0] < 200;
    bool right = lineSensors[1] < 200;

    if (left && right) return CENTER_LINE;
    if (left && !right) return LEFT_LINE;
    if (!left && right) return RIGHT_LINE;
    return OFF_LINE;
}