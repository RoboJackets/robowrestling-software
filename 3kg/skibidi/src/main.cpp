#include "Skibidi.hpp"

Skibidi* skibidi;
State state;

void setup(void) {
    // Serial initialization (for debugging)
    // Pin initialization -- handled by the things that use them
    // State initialization
    bool analog_line_sensors = false;
    skibidi = new Skibidi(analog_line_sensors);
    state = {
        .active_line_sensors = {
            {Position::FRONT_LEFT, false},
            {Position::FRONT_RIGHT, false},
            {Position::BACK_LEFT, false},
            {Position::BACK_RIGHT, false},
        },
        .active_ir_sensors = std::make_pair(false, false),
    };

    // Sensor initialization
    skibidi->initialize_sensors(analog_line_sensors);
}

void loop(void) {
    // TODO: Convert to interrupt, send Teensy
    // into low power at end of setup() and whenever
    // start module goes low @ match end
    StartModule* start_module = skibidi->get_start_module();
    if (!start_module->is_started()) {
        return;
    }

    // Update sensors
    skibidi->update_state(&state);

    // Checking if we hit the border somewhere
    if (state.active_line_sensors[Position::FRONT_LEFT] || state.active_line_sensors[Position::FRONT_RIGHT]) {
        // Emergency reverse
    } else if (state.active_line_sensors[Position::BACK_LEFT] || state.active_line_sensors[Position::BACK_RIGHT]) {
        // Emergency forward
    }

    // Make decision
    // Execute decision
}
