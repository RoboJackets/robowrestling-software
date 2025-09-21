#include "world_state.hpp"

const int threshold = 255;

// Constructor
world_state::world_state(int* line_sensors, int* ir_sensors) {
    this->line_sensors = line_sensors;
    this->ir_sensors = ir_sensors;

    // Initialize concurrency array
    for (int i = 0; i < 3; i++) {
        concurrency[i] = 0;
    }
}

// Existing functionality
void world_state::clean_sensors() {
    for (int i = 0; i < 3; i++) {
        if (ir_sensors[i] == 1) {
            if (concurrency[i] < 10) {
                concurrency[i]++;
            } else {
                concurrency[i] = 10;
            }
        } else {
            ir_sensors[i] = 0;
        }
    }
}

// New functionality (skeletons)

line_states world_state::line_check() {
    // TODO: implement logic using line_sensors

    bool zero_sensor[2];
    for (int i = 0; i < 2; i++) {
        zero_sensor[i] = (line_sensors[i] >= threshold) ? 1 : 0;
    }

    // Change States
    if (zero_sensor[0] == 0  && zero_sensor[1] == 0) {
        return line_states::SAFE;
    } else if (zero_sensor[0] == 1  && zero_sensor[1] == 0) {
        return line_states::LEFT;
    } else if (zero_sensor[0] == 0  && zero_sensor[1] == 1) {
        return line_states::RIGHT;
    } else {
        return line_states::UNSAFE;
    }
}

enemy_states world_state::enemy_pos() {
    // TODO: implement logic using ir_sensors

    if (ir_sensors[0] == 0 && ir_sensors[1] == 0 && ir_sensors[2] == 0) {
        return enemy_states::UNKNOWN;
    } else if (ir_sensors[0] == 0 && ir_sensors[1] == 0 && ir_sensors[2] == 1) {
        return enemy_states::RIGHT;
    } else if (ir_sensors[0] == 0 && ir_sensors[1] == 1 && ir_sensors[2] == 1) {
        return enemy_states::RIGHT;
    } else if (ir_sensors[0] == 1 && ir_sensors[1] == 0 && ir_sensors[2] == 0) {
        return enemy_states::LEFT;
    } else if (ir_sensors[0] == 1 && ir_sensors[1] == 1 && ir_sensors[2] == 0) {
        return enemy_states::LEFT;
    } else if (ir_sensors[0] == 0 && ir_sensors[1] == 1 && ir_sensors[2] == 0) {
        return enemy_states::FRONT;
    } else if (ir_sensors[0] == 1 && ir_sensors[1] == 0 && ir_sensors[2] == 1) {
        return enemy_states::FRONT;
    } else {
        return enemy_states::FRONT;
    }

}
