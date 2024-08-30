#include "Skibidi.hpp"

Skibidi::Skibidi() {
    this->line_sensors.insert(std::make_pair(LeftRight::LEFT, new DoubleLineSensor(1)));
    this->line_sensors.insert(std::make_pair(LeftRight::RIGHT, new DoubleLineSensor(1)));
}
