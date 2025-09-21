#include "world/sensors/line_sensor.hpp"
//software representation of the sensor
line_sensor :: line_sensor() {
    value = 0;
}

line_sensor :: line_sensor(int init_value) {
    value = init_value;
}
//returns ~0 on write, ~1000 on black
int line_sensor :: get_value() {
    return value;
}

void line_sensor :: set_value(int new_value) { 
    value = new_value;
}