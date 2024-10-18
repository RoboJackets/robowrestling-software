#include "robot/motor_driver.hpp"

motor_driver :: motor_driver() {
    motor_driver(true, 0);
}

motor_driver :: motor_driver(bool new_direction, int new_speed) {
    direction = new_direction;
    speed = new_speed;
}

void motor_driver :: set_direction(bool new_direction) {
    direction = new_direction;
}

void motor_driver :: set_speed(int new_speed) {
    speed = new_speed;
}

bool motor_driver :: get_direction() {
    return direction;
}

int motor_driver :: get_speed() {
    return speed;
}