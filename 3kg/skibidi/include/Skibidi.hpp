#ifndef SKIBIDI_HPP_
#define SKIBIDI_HPP_

#include <map>
#include <utility>
#include "MotorDriver.hpp"
#include "Sensors/DoubleLineSensor.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/StartModule.hpp"

enum Position { FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT, NONE };
enum IrDirection { LEFT, MID_LEFT, CENTER_LEFT, CENTER, CENTER_RIGHT, MID_RIGHT, RIGHT };

struct State {
    // maybe find a better way to do the line sensors so a switch-case
    // can be used instead of an if-elseif
    std::map<Position, bool> active_line_sensors;
    std::map<IrDirection, bool> active_ir_sensors;

    DrivingState driving_state;
    int motor_speed;
};

class Skibidi {
    private:
        std::map<Position, DoubleLineSensor*> line_sensors;
        std::map<IrDirection, IrSensor*> ir_sensors;
        MotorDriver* motor_driver;
        StartModule* start_module;

        void check_line_sensors(State* state);
    public:
        Skibidi(bool analog_line_sensors);

        StartModule* get_start_module();
        void initialize_sensors(bool analog_line_sensors);
        void update_state(State* state);
};

#endif // SKIBIDI_HPP_
