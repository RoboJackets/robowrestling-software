#include "Skibidi.hpp"

Skibidi::Skibidi(bool analog_line_sensors) {
    if (analog_line_sensors) {
        this->line_sensors.insert(std::make_pair(Position::FRONT_LEFT, new DoubleLineSensor(1, 2)));
        this->line_sensors.insert(std::make_pair(Position::FRONT_RIGHT, new DoubleLineSensor(1, 2)));
        this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1, 2)));
        this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1, 2)));
    } else {
        this->line_sensors.insert(std::make_pair(Position::FRONT_LEFT, new DoubleLineSensor(1)));
        this->line_sensors.insert(std::make_pair(Position::FRONT_RIGHT, new DoubleLineSensor(1)));
        this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1)));
        this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1)));
    }

    this->ir_sensors = std::make_pair(new IrSensor(1), new IrSensor(1));

    this->start_module = new StartModule(1);
    this->state = {
        .active_line_sensors = {
            {Position::FRONT_LEFT, false},
            {Position::FRONT_RIGHT, false},
            {Position::BACK_LEFT, false},
            {Position::BACK_RIGHT, false},
        },
        .active_ir_sensors = std::make_pair(false, false),
    };
}

StartModule* Skibidi::get_start_module() {
    return this->start_module;
}

struct State* Skibidi::get_state() {
    return &state;
}

void Skibidi::check_line_sensors() {
    for (auto it = this->line_sensors.begin(); it != this->line_sensors.end(); ++it) {
        this->state.active_line_sensors[it->first] = it->second->is_sensing();
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

void Skibidi::update_state() {
    this->check_line_sensors();
    this->state.active_ir_sensors.first = this->ir_sensors.first->is_sensing();
    this->state.active_ir_sensors.second = this->ir_sensors.second->is_sensing();
}
