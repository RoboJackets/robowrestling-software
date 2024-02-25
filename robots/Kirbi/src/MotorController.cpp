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

    int mappedLeft = map(speed, -100, 100, 1, 127);
    int mappedRight = map(speed, -100, 100, 128, 255);

    _sendCommand(mappedLeft, mappedRight);
}

void MotorController::move(int leftSpeed, int rightSpeed) {
    if (leftSpeed < -100 || leftSpeed > 100) return;
    if (rightSpeed < -100 || rightSpeed > 100) return;

    int mappedLeft = map(leftSpeed, -100, 100, 1, 127);
    int mappedRight = map(rightSpeed, -100, 100, 128, 255);

    _sendCommand(mappedLeft, mappedRight);
}

void MotorController::turn(int speed) {
    // Protect from improper values
    if (speed < -100 || speed > 100) return;
    if (speed == _last_turn_speed) return;
    _last_turn_speed = speed;

    int mappedLeft = map(speed, -100, 100, 1, 127);
    int mappedRight = -1 * (map(speed, -100, 100, 128, 255)); // Inverted so motors spin opposite directions

    _sendCommand(mappedLeft, mappedRight);
}

void MotorController::stop() {
    // Values exactly in the middle of both ranges
    // tell the motor controller to stop the motors
    _sendCommand(64, 192);
}

void MotorController::_sendCommand(int leftSpeed, int rightSpeed) {
    // This is just how the motor controller receives values
    uint8_t speeds[2];
    speeds[0] = leftSpeed;
    speeds[1] = rightSpeed;

    // The 2 means that we're writing two bytes
    _serial->write(speeds, 2);
}
