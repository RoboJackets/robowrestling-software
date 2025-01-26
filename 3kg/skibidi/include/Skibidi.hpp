#ifndef SKIBIDI_HPP_
#define SKIBIDI_HPP_

#include <map>
#include <utility>
#include "Sensors/DoubleLineSensor.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/StartModule.hpp"

enum Position { FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT, NONE };

struct State {
    // maybe find a better way to do the line sensors so a switch-case
    // can be used instead of an if-elseif
    std::map<Position, bool> active_line_sensors;
    std::pair<bool, bool> active_ir_sensors;
    // Stuff here for current behavior,
    // root behavior (? - can just do circ. linked list), etc
};

class Skibidi {
    private:
        std::map<Position, DoubleLineSensor*> line_sensors;
        std::pair<IrSensor*, IrSensor*> ir_sensors;
        StartModule* start_module;
        struct State state;

        void check_line_sensors();
    public:
        Skibidi(bool analog_line_sensors);

        StartModule* get_start_module();
        struct State* get_state();
        void initialize_sensors(bool analog_line_sensors);
        void update_state();
};

#endif // SKIBIDI_HPP_
