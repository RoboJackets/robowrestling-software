#include "Robot/World_State.hpp"

WorldState::WorldState(int line[2], int ir[4]) {
    for (int i = 0; i < 2; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 4; i++) {
        ir_sensors[i] = ir[i];
    }
}

void WorldState::update_sensors(int line[2], int ir[4]) {
    for (int i = 0; i < 2; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 4; i++) {
        ir_sensors[i] = ir[i];
    }
}

line_states WorldState::line_check() {
    // Simple line check for two sensors (left, right)
    if (line_sensors[0] < 700) {
        return TopLeft;
    }
    if (line_sensors[1] < 700) {
        return TopRight;
    }
    return NoneLine;
}

enemy_states WorldState::enemy_pos() {
    // Simple IR mapping (SideLeft, FrontLeft, FrontRight, SideRight)
    if (ir_sensors[1] == 1 || ir_sensors[2] == 1) {
        return Front;
    }
    if (ir_sensors[0] == 1) {
        return Left;
    }
    if (ir_sensors[3] == 1) {
        return Right;
    }
    return NoneEnemy;
}
