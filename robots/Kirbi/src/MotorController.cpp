#include "MotorController.h"

// See include/MotorController.h for more detailed comments
// about how this works.

MotorController::MotorController(Stream* serial) {
    _serial = serial;
    _last_turn_speed = 0;
    _last_move_speed = 0;
}

void MotorController::move(int speed) {
    // Protect from improper values
    if (speed < -100 || speed > 100) return;
    _last_move_speed = speed;

    int mapped_first = map(speed, -100, 100, 1, 127);
    int mapped_second = map(speed, -100, 100, 128, 255);

    uint8_t msg[2];
    msg[0] = mapped_first;
    msg[1] = mapped_second;
    _serial -> write(msg, 2);
}

void MotorController::move(int leftSpeed, int rightSpeed) {
    if (leftSpeed < -100 || leftSpeed > 100) return;
    if (rightSpeed < -100 || rightSpeed > 100) return;

    int mappedLeft = map(leftSpeed, -100, 100, 1, 127);
    int mappedRight = map(rightSpeed, -100, 100, 128, 255);
    uint8_t msg[2];
    msg[0] = mappedLeft;
    msg[1] = mappedRight;
    _serial -> write(msg, 2);
}

void MotorController::turn(int speed) {
    // Protect from improper values
    if (speed < -100 || speed > 100) return;
    if (speed == _last_turn_speed) return;
    _last_turn_speed = speed;

    int mapped_first = map(speed, -100, 100, 1, 127);
    int mapped_second = -1 * (map(speed, -100, 100, 128, 255)); // Inverted so motors spin opposite directions
    _serial -> write(mapped_first);
    _serial -> write(mapped_second);
}

void MotorController::stop() {
    uint8_t speeds[2];
    speeds[0] = 64;
    speeds[1] = 192;
    _serial -> write(speeds, 2);
}
