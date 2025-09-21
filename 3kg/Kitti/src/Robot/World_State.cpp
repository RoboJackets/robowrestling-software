#include "Robot/World_State.hpp"

WorldState::WorldState(int line[4], int ir[9]) {
    for (int i = 0; i < 4; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 9; i++) {
        ir_sensors[i] = ir[i];
    }
}

void WorldState::update_sensors(int line[4], int ir[9]) {
    for (int i = 0; i < 4; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 9; i++) {
        ir_sensors[i] = ir[i];
    }
}

line_states WorldState::line_check() {
    // TODO: Implement line_check()
    if (line_sensors[0] == 1) {
        return TopLeft;
    } else if (line_sensors[1] == 1) {
        return TopRight;
    } else if (line_sensors[2] == 1) {
        return BottomLeft;
    } else if (line_sensors[3] == 1) {
        return BottomRight;
    } else {
        return NoneLine;
    }
}

enemy_states WorldState::enemy_pos() {
    // TODO: Implement enemy_pos()
    if (ir_sensors[3] == 1 || ir_sensors[4] == 1 || ir_sensors[5] == 1) {
        return Front;
    } else if (ir_sensors[2] == 1 || ir_sensors[1] == 1) {
        return Left;
    } else if (ir_sensors[6] == 1 || ir_sensors[7] == 1) {
        return Right;
    } else if (ir_sensors[0] == 1 || ir_sensors[8] == 1) {
        return Back;
    } else {
        return NoneEnemy;
    }
}
