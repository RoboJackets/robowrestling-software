#include <Arduino.h>
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
        for (const auto& [posn, sensor] : skibidi->get_line_sensors()) {
            sensor->calibrate_analog();
        }
    }
}

void loop(void) {
    // Update sensors
    // Make decision
    // Execute decision
}
