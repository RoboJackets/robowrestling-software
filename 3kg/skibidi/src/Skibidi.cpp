#include "Skibidi.hpp"

Skibidi::Skibidi(bool analog_line_sensors) {
    if (analog_line_sensors) {
       this->line_sensors = {
            {Position::FRONT_LEFT,  new DoubleLineSensor(1, 2)},
            {Position::FRONT_RIGHT, new DoubleLineSensor(1, 2)},
            {Position::BACK_LEFT,   new DoubleLineSensor(1, 2)},
            {Position::BACK_RIGHT,  new DoubleLineSensor(1, 2)},
       };
    } else {
       this->line_sensors = {
            {Position::FRONT_LEFT,  new DoubleLineSensor(1)},
            {Position::FRONT_RIGHT, new DoubleLineSensor(1)},
            {Position::BACK_LEFT,   new DoubleLineSensor(1)},
            {Position::BACK_RIGHT,  new DoubleLineSensor(1)},
       };
    }

    this->ir_sensors = {
        {IrDirection::RIGHT,        new IrSensor(1)},
        {IrDirection::MID_RIGHT,    new IrSensor(1)},
        {IrDirection::CENTER_RIGHT, new IrSensor(1)},
        {IrDirection::CENTER,       new IrSensor(1)},
        {IrDirection::CENTER_LEFT,  new IrSensor(1)},
        {IrDirection::MID_LEFT,     new IrSensor(1)},
        {IrDirection::LEFT,         new IrSensor(1)},
    };
    this->motor_driver = new MotorDriver(std::make_pair(1, 2), std::make_pair(1, 2));

    this->start_module = new StartModule(1);
}

StartModule* Skibidi::get_start_module() {
    return this->start_module;
}

void Skibidi::check_line_sensors(State* state) {
    for (auto it = this->line_sensors.begin(); it != this->line_sensors.end(); ++it) {
        state->active_line_sensors[it->first] = it->second->is_sensing();
    }
}

void Skibidi::initialize_sensors(bool analog_line_sensors) {
    if (analog_line_sensors) {
        // This SHOULD be fine because this will occur
        // after the bot is sat on the dohyo and started
        // but BEFORE the match begins
        std::map<Position, DoubleLineSensor*> line_sensors = this->line_sensors;
        for (auto it = line_sensors.begin(); it != line_sensors.end(); ++it) {
            it->second->calibrate_analog();
        }
    }
}

void Skibidi::update_state(State* state) {
    this->check_line_sensors(state);
    for (auto it = ir_sensors.begin(); it != ir_sensors.end(); ++it) {
        state->active_ir_sensors[it->first] = it->second->is_sensing();
    }
}

void Skibidi::execute_action(State* state) {
    this->motor_driver->change_state(state->driving_state);
    this->motor_driver->drive(state->motor_speed);
}
