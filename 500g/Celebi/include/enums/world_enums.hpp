#ifndef WORLD_ENUM_H
#define WORLD_ENUM_H

enum line_states {
    LEFT_ON,
    RIGHT_ON,
    BOTH_ON,
    OFF
};

enum enemy_states {
    LEFT,
    FRONT_LEFT,
    FRONT,
    FRONT_RIGHT,
    RIGHT,
    CLOSE_LEFT,
    CLOSE_MID_LEFT,
    CLOSE_MID,
    CLOSE_MID_RIGHT,
    CLOSE_RIGHT,
    UNKNOWN
};

#endif