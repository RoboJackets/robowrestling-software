#ifndef ROBOT_ENUM_H
#define ROBOT_ENUM_H


enum movement_states {
    DRIVE_FORWARD,
    DRIVE_BACKWARD,
    TURN_LEFT,
    TURN_RIGHT
};

enum approach_state {
    TURN,
    GO_STRAIGHT,
    GO_BACKWARDS
};
#endif