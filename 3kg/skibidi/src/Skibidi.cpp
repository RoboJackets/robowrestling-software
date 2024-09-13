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
}

std::map<Position, DoubleLineSensor*> Skibidi::get_line_sensors() {
    return this->line_sensors;
}

const StartModule* Skibidi::get_start_module() {
    return this->start_module;
}
