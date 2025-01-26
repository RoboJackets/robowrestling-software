#include "Actions/SlammyWhammyImproved.hpp"

SlammyWhammy::SlammyWhammy() {
    this->last_seen = Direction::NONE;
}

void SlammyWhammy::make_decision(State* state) {
    if (state->active_ir_sensors.first && state->active_ir_sensors.second) {
        // Directly in front, charge
    } else if (!(state->active_ir_sensors.first || state->active_ir_sensors.second)) {
        switch(this->last_seen) {
            case Direction::NONE:
                // We don't know, so bias left
                // Should only show up upon bot start
            case Direction::LEFT:
                break;
            case Direction::RIGHT:
                break;
        }
    } else {
        // Turn towards the sensor that is detecting
    }
}
