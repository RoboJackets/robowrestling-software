#ifndef WORLD_ENUM_H
#define WORLD_ENUM_H

enum line_states {
    OFF,
    LEFT_ON,
    RIGHT_ON,
    BOTH_ON
};

enum enemy_states {
    LEFT,
    FRONT_LEFT,
    FRONT,
    FRONT_RIGHT,
    RIGHT,
    //unused for 3 sensors
    CLOSE_LEFT,
    CLOSE_MID_LEFT,
    CLOSE_MID,
    CLOSE_MID_RIGHT,
    //unused for 3 sensors
    CLOSE_RIGHT,
    UNKNOWN
};

#endif