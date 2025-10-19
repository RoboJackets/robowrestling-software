#include "Strategies/Matador.hpp"

void Matador::make_decision(State* state) {
    if (this->turn_complete && this->rev_complete) {
        this->track.make_decision(state);
    } else if (this->initiated_matador) {
        if (!this->turn_complete) {
            state->driving_state = MTURN_RIGHT;
            state->motor_speed = this->rev_speed;

            if (millis() - this->millis_tracker >= TURN_MILLIS) {
                this->turn_complete = true;
                this->millis_tracker = millis();
            }
        } else if (!this->rev_complete) {
            state->driving_state = MBACKWARD;
            state->motor_speed = this->rev_speed;

            if (millis() - this->millis_tracker >= REVERSE_MILLIS) {
                this->rev_complete = true;
                state->driving_state = MBRAKE;
                state->motor_speed = 0;
            }
        }
    } else if (state->active_ir_sensors[IrDirection::CENTER_LEFT]
        && state->active_ir_sensors[IrDirection::CENTER]
        && state->active_ir_sensors[IrDirection::CENTER_RIGHT]
    ) {
        this->initiated_matador = true;
        this->millis_tracker = millis();

        // Begin turning
        state->driving_state = MTURN_RIGHT;
        state->motor_speed = this->rev_speed;
    } else {
        this->slammy_whammy.make_decision(state);
    }
}

Matador::Matador(int charge_speed, int rev_speed) {
    this->charge_speed = charge_speed;
    this->rev_speed = rev_speed;
}
