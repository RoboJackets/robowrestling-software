#include "Actions/Defense.hpp"

void Defense::make_decision(State *state) {
    switch (this->phase) {
        case PRE_FLINCH:
            this->flinch_started_millis = millis();
            this->phase = Phase::FLINCHING;
            // Fall-through is deliberate
        case FLINCHING:
            this->phase = (millis() - this->flinch_started_millis)
                >= FLINCH_MILLIS ? Phase::PRE_INCH : Phase::FLINCHING;
            state->driving_state = DrivingState::MFORWARD;
            state->motor_speed = 50;
            break;

        case PRE_INCH:
            this->phase = (millis() - (this->flinch_started_millis + FLINCH_MILLIS))
                >= UNTIL_INCH_MILLIS ? Phase::INCH_FWD : Phase::PRE_INCH;
            state->motor_speed = 0;
            break;

        case INCH_START:
            this->inch_started_millis = millis();
            this->phase = Phase::INCH_FWD;
            // Fall-through is deliberate
        case INCH_FWD:
            // TODO: adjust to turn towards opponent if opponent moves
            this->phase = (millis() - this->inch_started_millis)
                >= INCH_MILLIS ? Phase::INCH_WAIT : Phase::INCH_FWD;
            state->driving_state = DrivingState::MFORWARD;
            state->motor_speed = 50;
            break;

        case INCH_WAIT:
            this->phase = (millis() - (this->inch_started_millis + INCH_MILLIS))
                >= INCH_WAIT_MILLIS ? Phase::INCH_START : Phase::INCH_WAIT;

            // NOTE: will have center sensor tuned to detect only
            // at close range
            this->phase = state->active_ir_sensors[IrDirection::CENTER]
                ? Phase::CHARGING : this->phase;

            state->motor_speed = 0;

            break;

        case CHARGING:
            // TODO: import slammy whammy logic or otherwise
            // delegate to slammy whammy
            break;
    }
}

Defense::Defense() {
    this->phase = Phase::PRE_FLINCH;
    this->flinch_started_millis = -1;
    this->inch_started_millis = -1;
}
