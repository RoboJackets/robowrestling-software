#include "Robot/World_State.hpp"

WorldState::WorldState(int line[4], int ir[9]) {
    for (int i = 0; i < 4; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 9; i++) {
        ir_sensors[i] = ir[i];
    }
}

line_states WorldState::line_check() {
    // TODO: Implement line_check()
}

enemy_states WorldState::enemy_pos() {
    // TODO: Implement enemy_pos()
}
