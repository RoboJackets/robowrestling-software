#include "world_state.hpp"
#include <Arduino.h>

world_state::world_state(int* sensors) {
    ir_sensors = sensors;
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