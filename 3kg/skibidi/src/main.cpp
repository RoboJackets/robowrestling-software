#include "Strategies/Strategy.hpp"
#include "Strategies/SlammyWhammyImproved.hpp"
#include "Skibidi.hpp"

Skibidi *skibidi;
State state;
Strategy *strategy;

void setup(void) {
    // Serial initialization (for debugging)
    Serial.begin(9600);
    // Pin initialization -- handled by the things that use them
    // State initialization
    skibidi = new Skibidi();
    state = {
        .active_line_sensors = {
            {Position::FRONT_LEFT,  false},
            {Position::FRONT_RIGHT, false},
            {Position::BACK_LEFT,   false},
            {Position::BACK_RIGHT,  false},
        },
        .active_ir_sensors = {
            {IrDirection::RIGHT,        false},
            {IrDirection::MID_RIGHT,    false},
            {IrDirection::CENTER_RIGHT, false},
            {IrDirection::CENTER,       false},
            {IrDirection::CENTER_LEFT,  false},
            {IrDirection::MID_LEFT,     false},
            {IrDirection::LEFT,         false},
        },
    };
    strategy = new SlammyWhammy(50, 30);

    // Sensor initialization
    skibidi->initialize_sensors();
}

char* linetos(Position ir) {
    switch (ir) {
        case Position::FRONT_LEFT:  return (char*)"FRONT_LEFT\0";
        case Position::FRONT_RIGHT: return (char*)"FRONT_RIGHT\0";
        case Position::BACK_LEFT:   return (char*)"BACK_LEFT\0";
        case Position::BACK_RIGHT:  return (char*)"BACK_RIGHT\0";
        case Position::NONE:        return (char*)"NONE\0";
    }
    return (char*)"NONE";
}

void loop(void) {
    // TODO: Convert to interrupt, send Teensy
    // into low power at end of setup() and whenever
    // start module goes low @ match end
    StartModule* start_module = skibidi->get_start_module();
    if (!start_module->is_started()) {
        state.driving_state = DrivingState::MBRAKE;
        state.motor_speed = 0;
        state.tank_drive = false;
        skibidi->execute_action(&state);
        return;
    }

    // Update sensors
    skibidi->update_state(&state);

    // Checking if we hit the border somewhere
    if (state.emergency_mvmt && millis() - state.emerg_started_millis < EMERG_MVMT_MILLIS) {
        // do nothing, continue backing up
    } else if (state.active_line_sensors[Position::FRONT_LEFT] || state.active_line_sensors[Position::FRONT_RIGHT]) {
        // Emergency reverse
        state.emergency_mvmt = true;
        state.emerg_started_millis = millis();
        state.driving_state = DrivingState::MBACKWARD;
        state.motor_speed = 10;
        Serial.println("Emergency back");
    } else {
        // Make decision
        strategy->make_decision(&state);
    }

    // Execute decision
    skibidi->execute_action(&state);
}
