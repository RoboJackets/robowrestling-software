#ifndef SKIBIDI_HPP_
#define SKIBIDI_HPP_

#include <map>
#include <utility>
#include "Sensors/DoubleLineSensor.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/StartModule.hpp"

enum Position { FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT };

class Skibidi {
    private:
        std::map<Position, DoubleLineSensor*> line_sensors;
        std::pair<IrSensor*, IrSensor*> ir_sensors;
        StartModule* start_module;
    public:
        Skibidi(bool analog_line_sensors);

        std::map<Position, DoubleLineSensor*> get_line_sensors();
        StartModule* get_start_module();
};

#endif // SKIBIDI_HPP_
