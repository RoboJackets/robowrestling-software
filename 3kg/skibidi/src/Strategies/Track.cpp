#include "Strategies/Track.hpp"

Track::Track(int fwd_speed, int turn_speed) {
    this->fwd_speed = fwd_speed;
    this->turn_speed = turn_speed;
}

int map_range(int old_min, int old_max, int new_min, int new_max, int val) {
    /**
     *  OldRange = (OldMax - OldMin) = 100 - 0 = 100
     *  NewRange = (NewMax - NewMin) 255 - 0 = 255
     *
     *  NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
     */
    int old_range = old_max - old_min;
    int new_range = new_max - new_min;
    return (((val - old_min) * new_range) / old_range) + new_min;
}

void Track::make_decision(State* state) {
    int left_bias = 20, right_bias = 20;
    left_bias += (int)state->active_ir_sensors[IrDirection::CENTER_LEFT]*10
        + (int)state->active_ir_sensors[IrDirection::MID_LEFT]*30
        + (int)state->active_ir_sensors[IrDirection::LEFT]*40;
    right_bias += (int)state->active_ir_sensors[IrDirection::CENTER_RIGHT]*10
        + (int)state->active_ir_sensors[IrDirection::MID_RIGHT]*30
        + (int)state->active_ir_sensors[IrDirection::RIGHT]*40;

    int left_spd_adj, right_spd_adj;
    if (left_bias == 20 && right_bias == 20 && !state->active_ir_sensors[IrDirection::CENTER]) {
        left_spd_adj = map_range(0, 100, 0, this->turn_speed, 100);
        right_spd_adj = 0;
    } else {
        // Reversed because if left is sensing then
        // right needs to turn more and vice versa
        left_spd_adj = map_range(0, 100, 0, this->turn_speed, right_bias);
        right_spd_adj = map_range(0, 100, 0, this->turn_speed, left_bias);
    }

    state->driving_state = DrivingState::MFORWARD;
    state->tank_drive = true;
    state->left_speed = left_spd_adj;
    state->right_speed = right_spd_adj;
}
