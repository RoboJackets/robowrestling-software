#include "Robot/World_State.hpp"

WorldState::WorldState(int line[4], int ir[7]) {
    for (int i = 0; i < 4; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 7; i++) {
        ir_sensors[i] = ir[i];
    }
}

void WorldState::update_sensors(int line[4], int ir[7]) {
    for (int i = 0; i < 4; i++) {
        line_sensors[i] = line[i];
    }
    for (int i = 0; i < 7; i++) {
        ir_sensors[i] = ir[i];
    }
}

line_states WorldState::line_check() {
    // Simple line check for two sensors (left, right)
    if (line_sensors[0] < 700) {
        return FL_Line;
    }
    if (line_sensors[1] < 700) {
        return FR_Line;
    }
    if (line_sensors[2] < 700) {
        return BR_Line;
    }
    if (line_sensors[3] < 700) {
        return BL_Line;
    }
    return NoneLine;
}

enemy_states WorldState::enemy_pos() {
    // Simple IR mapping (SideLeft, FrontLeft, FrontRight, SideRight)
    if (ir_sensors[0] == 1) {
        return Back_IR;
    }
    if (ir_sensors[4] == 1 && ir_sensors[3] == 1) {
        return Front_IR;
    }
    if (ir_sensors[4] == 1) {
        return FR_IR;
    }
    if (ir_sensors[3] == 1) {
        return FL_IR;
    }
    if (ir_sensors[2] == 1) {
        return FL45_IR;
    }
    if (ir_sensors[5] == 1) {
        return FR45_IR;
    }
    if (ir_sensors[1] == 1) {
        return Left_IR;
    }
    if (ir_sensors[6] == 1) {
        return Right_IR;
    }
    return NoneEnemy;
}
