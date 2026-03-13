#ifndef ROBOT_ENUM_H
#define ROBOT_ENUM_H


enum draw_state {
    D_TURN,
    D_GO_STRAIGHT,
    D_GO_BACKWARDS
};

enum swerve_state {
    S_UNKNOWN,
    S_TURN_AWAY,
    S_GO_STRAIGHT,
    S_TURN_BACK,
    S_ATTACK
};

enum attack_state {
    A_SEE,
    A_LOOKING,
    A_BLIND,
    A_DOGE
};
#endif