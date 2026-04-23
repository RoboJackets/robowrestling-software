#ifndef WORLD_ENUM_H
#define WORLD_ENUM_H

#include <stdint.h>

enum line_states: uint8_t {
    OFF,
    LEFT_ON,
    RIGHT_ON,
    BOTH_ON
};

enum enemy_states: uint8_t {
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