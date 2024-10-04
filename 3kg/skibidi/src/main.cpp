#include <Arduino.h>
#include "Sensors/DoubleLineSensor.hpp"
#include "Skibidi.hpp"

Skibidi* skibidi;

void setup(void) {
    // Serial initialization (for debugging)
    // Pin initialization -- handled by the things that use them
    // State initialization
    bool analog_line_sensors = false;
    skibidi = new Skibidi(analog_line_sensors);

    // Sensor initialization
    if (analog_line_sensors) {
        // This SHOULD be fine because this will occur
        // after the bot is sat on the dohyo and started
        // but BEFORE the match begins
        std::map<Position, DoubleLineSensor*> line_sensors = skibidi->get_line_sensors();
        for (auto it = line_sensors.begin(); it != line_sensors.end(); ++it) {
            it->second->calibrate_analog();
        }
    }
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

    // Checking if we hit the border somewhere
    switch(skibidi->check_line_sensors()) {
        case BACK_LEFT:
        case BACK_RIGHT:
            // Move forward
            break;
        case FRONT_LEFT:
        case FRONT_RIGHT:
            // Move backward
            break;
        case NONE:
            break;
    }
    // Make decision
    // Execute decision
}
