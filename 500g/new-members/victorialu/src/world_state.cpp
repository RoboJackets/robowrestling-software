#include "world_state.hpp"

world_state::world_state(int* ir, int* line) {
    ir_sensors = ir;
    line_sensors = line;
}

//use line_sensors array to decide where the robot is
line_states world_state::line_check() {
    int leftVal = line_sensors[0];
    int rightVal = line_sensors[1];

    int threshold = 650;

    bool leftOnLine = (leftVal < threshold);
    bool rightOnLine = (rightVal < threshold);

    if (leftOnLine && rightOnLine) return LINE_BOTH_WHITE;
    else if (leftOnLine) return LINE_LEFT_WHITE;
    else if (rightOnLine) return LINE_RIGHT_WHITE   ;
    else return LINE_BOTH_BLACK;
}

//use ir_sensors array to decide where the enemy is
enemy_states world_state::enemy_pos() {
    bool left = ir_sensors[0] == 1;
    int center = ir_sensors[1] == 1;
    int right = ir_sensors[2] == 1;

    if (!left && !center && !right) return ENEMY_NONE;
    if (left && !center && !right) return ENEMY_LEFT;
    if (!left && center && !right) return ENEMY_CENTER;
    if (!left && !center && right) return ENEMY_RIGHT;
    if (left && center && !right) return ENEMY_LEFT_CENTER;
    if (!left && center && right) return ENEMY_CENTER_RIGHT;
    if (left && !center && right) return ENEMY_LEFT_RIGHT;
    if (left && center && right) return ENEMY_ALL;

    return ENEMY_NONE;
}

void world_state::clean() {
    ir_sensors[0] = 0;
    ir_sensors[1] = 0;
    ir_sensors[2] = 0;
    line_sensors[0] = 0;
    line_sensors[1] = 0;
}


