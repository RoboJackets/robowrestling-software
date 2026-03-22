#include "Actions/SlammyWhammyImproved.hpp"

SlammyWhammy::SlammyWhammy() {
    this->last_seen = Direction::DNONE;
}

void SlammyWhammy::make_decision(State* state) {
    bool center_sensing = state->active_ir_sensors[IrDirection::CENTER]
                        || state->active_ir_sensors[IrDirection::CENTER_LEFT]
                        || state->active_ir_sensors[IrDirection::CENTER_RIGHT];
    bool left_sensing = state->active_ir_sensors[IrDirection::LEFT]
                        || state->active_ir_sensors[IrDirection::MID_LEFT];
    bool right_sensing = state->active_ir_sensors[IrDirection::RIGHT]
                        || state->active_ir_sensors[IrDirection::MID_RIGHT];

    if (center_sensing) {
        // Directly in front, charge
        state->driving_state = DrivingState::MFORWARD;
        state->motor_speed = 10;
    } else if (!(center_sensing || left_sensing || right_sensing)) {
        switch(this->last_seen) {
            case Direction::DNONE:
                // We don't know, so bias left
                // Should only show up upon bot start
            case Direction::DLEFT:
                state->driving_state = DrivingState::MTURN_LEFT;
                break;
            case Direction::DRIGHT:
                state->driving_state = DrivingState::MTURN_RIGHT;
                break;
        }
        state->motor_speed = 5;
    } else {
        // Turn towards side that is sensing
        this->last_seen = left_sensing ? Direction::DLEFT : Direction::DRIGHT;
        state->driving_state = left_sensing ? DrivingState::MTURN_LEFT : DrivingState::MTURN_RIGHT;
        state->motor_speed = 5;
    }
}
