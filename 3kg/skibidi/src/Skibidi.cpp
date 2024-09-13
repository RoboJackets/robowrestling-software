#include "Skibidi.hpp"

Skibidi::Skibidi() {
    this->line_sensors.insert(std::make_pair(Position::FRONT_LEFT, new DoubleLineSensor(1)));
    this->line_sensors.insert(std::make_pair(Position::FRONT_RIGHT, new DoubleLineSensor(1)));
    this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1)));
    this->line_sensors.insert(std::make_pair(Position::BACK_RIGHT, new DoubleLineSensor(1)));

    this->ir_sensors = std::make_pair(new IrSensor(1), new IrSensor(1));

    this->start_module = new StartModule(1);
}
