#include "world/sensors/ir_sensor.hpp"
//software representation of the sensor
ir_sensor :: ir_sensor() {
    ir_sense = false;
}

ir_sensor :: ir_sensor(bool init_value) {
    ir_sense = init_value;
}

bool ir_sensor :: get_ir_sense() {
    return ir_sense;
}

void ir_sensor :: set_ir_sense(bool new_value) { 
    ir_sense = new_value;
}