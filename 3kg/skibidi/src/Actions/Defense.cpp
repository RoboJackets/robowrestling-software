#include "Actions/Defense.hpp"

void Defense::make_decision(State *state) {
    if (!this->have_flinched) {
        if (this->flinch_started_millis == -1)
            this->flinch_started_millis = millis();

        this->have_flinched =
            (millis() - this->flinch_started_millis) >= FLINCH_MILLIS;
        state->driving_state = DrivingState::MFORWARD;
        state->motor_speed = 50;
    }
}

Defense::Defense() {
    this->have_flinched = false;
    this->flinch_started_millis = -1;
}
