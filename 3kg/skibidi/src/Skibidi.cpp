#include "Skibidi.hpp"

Skibidi::Skibidi(void) {
    this->line_sensors = {
        {Position::FRONT_LEFT,  new DoubleLineSensor(17)},
        {Position::FRONT_RIGHT, new DoubleLineSensor(15)},
        //{Position::BACK_LEFT,   new DoubleLineSensor(1)},
        //{Position::BACK_RIGHT,  new DoubleLineSensor(1)},
    };

    this->ir_sensors = {
        {IrDirection::LEFT,        new IrSensor(2)},
        {IrDirection::MID_LEFT,    new IrSensor(3)},
        {IrDirection::CENTER_LEFT, new IrSensor(4)},
        {IrDirection::CENTER,       new IrSensor(5)},
        {IrDirection::CENTER_RIGHT,  new IrSensor(6)},
        {IrDirection::MID_RIGHT,     new IrSensor(9)},
        {IrDirection::RIGHT,         new IrSensor(10)},
    };
    //this->motor_driver = new MotorDriver(std::make_pair(1, 2), std::make_pair(1, 2));
    this->motor_driver = new MotorDriver(11, 12, 36, 39, 38, 37);

    this->start_module = new StartModule(13);
}

StartModule* Skibidi::get_start_module() {
    return this->start_module;
}

void Skibidi::check_line_sensors(State* state) {
    for (auto it = this->line_sensors.begin(); it != this->line_sensors.end(); ++it) {
        state->active_line_sensors[it->first] = it->second->is_sensing();
    }
}

void Skibidi::initialize_sensors() {
    std::map<Position, DoubleLineSensor*> line_sensors = this->line_sensors;
    for (auto it = line_sensors.begin(); it != line_sensors.end(); ++it) {
        it->second->calibrate();
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

    if (state->tank_drive)
        this->motor_driver->drive(state->left_speed, state->right_speed);
    else
        this->motor_driver->drive(state->motor_speed);
}
