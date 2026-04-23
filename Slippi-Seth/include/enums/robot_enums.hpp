#ifndef ROBOT_ENUM_H
#define ROBOT_ENUM_H

#include <stdint.h>

enum draw_state: uint8_t {
    D_TURN,
    D_GO_STRAIGHT,
    D_GO_BACKWARDS
};

enum swerve_state: uint8_t {
    S_UNKNOWN,
    S_TURN_AWAY,
    S_GO_STRAIGHT,
    S_TURN_BACK,
    S_ATTACK
};

enum attack_state: uint8_t {
    A_SEE,
    A_LOOKING,
    A_BLIND,
    A_DOGE
};

enum match_start: uint8_t {
    SET_TIMER,
    START,
    START_FINISHED
};

enum strategy: uint8_t {
    BASE,
    CLOSE,
    MEDIUM,
    FAR
};
#endif