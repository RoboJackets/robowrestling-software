#include "Actions/SlammyWhammyImproved.hpp"

SlammyWhammy::SlammyWhammy() {
    this->last_seen = Direction::DNONE;
}

void SlammyWhammy::make_decision(State* state) {
    bool center_sensing = state->active_ir_sensors[IrDirection::CENTER];
    bool left_sensing = state->active_ir_sensors[IrDirection::LEFT]
                        || state->active_ir_sensors[IrDirection::MID_LEFT]
                        || state->active_ir_sensors[IrDirection::CENTER_LEFT];
    bool right_sensing = state->active_ir_sensors[IrDirection::RIGHT]
                        || state->active_ir_sensors[IrDirection::MID_RIGHT]
                        || state->active_ir_sensors[IrDirection::CENTER_RIGHT];

    if (center_sensing || (state->active_ir_sensors[CENTER_RIGHT] && state->active_ir_sensors[CENTER_LEFT])) {
        // Directly in front, charge
    } else if (!(center_sensing || left_sensing || right_sensing)) {
        switch(this->last_seen) {
            case Direction::DNONE:
                // We don't know, so bias left
                // Should only show up upon bot start
            case Direction::DLEFT:
                break;
            case Direction::DRIGHT:
                break;
        }
    } else {
        // Turn towards side that is sensing
    }
}
