#include "Actions/Action.hpp"
#include "Actions/SlammyWhammyImproved.hpp"
#include "Skibidi.hpp"

Skibidi* skibidi;
State state;
Action *strategy;

void setup(void) {
    /*
    // Serial initialization (for debugging)
    // Pin initialization -- handled by the things that use them
    // State initialization
    bool analog_line_sensors = false;
    skibidi = new Skibidi(analog_line_sensors);
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
    strategy = new SlammyWhammy();

    // Sensor initialization
    skibidi->initialize_sensors(analog_line_sensors);
    */
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(25, OUTPUT);
   pinMode(36, OUTPUT);
   pinMode(37, OUTPUT);
   pinMode(24, OUTPUT);
}

void loop(void) {
    //skibidi->motor_driver->driving_state = DrivingState::MFORWARD;
    //skibidi->motor_driver->drive(50);
    //skibidi->motor_driver->driving_state = DrivingState::MBACKWARD;
    //skibidi->motor_driver->drive(50);

    digitalWrite(36, HIGH);
    digitalWrite(37, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    analogWrite(24, 128);
    analogWrite(25, 128);
    delay(1000);
    digitalWrite(36, LOW);
    digitalWrite(37, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    analogWrite(25, 128);
    analogWrite(24, 128);
    delay(1000);
}

/*
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
        state.driving_state = DrivingState::MBACKWARD;
        state.motor_speed = 75;
    } else if (state.active_line_sensors[Position::BACK_LEFT] || state.active_line_sensors[Position::BACK_RIGHT]) {
        // Emergency forward
        state.driving_state = DrivingState::MFORWARD;
        state.motor_speed = 75;
    } else {
        // Make decision
        strategy->make_decision(&state);
    }

    // Execute decision
    skibidi->execute_action(&state);
}
*/
