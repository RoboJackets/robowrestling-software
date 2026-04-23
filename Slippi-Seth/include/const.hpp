#ifndef CONST
#define CONST

#include "types.hpp"
const uint8_t max_speed = 255;
const uint8_t med_turn = 179;
const uint8_t fast_turn = 205;

//powers first, then time
// none, close, medium, far (left), straight line, close, medium, far (right)
const start_info start_data = {
    {
        0, 
        70, 100, 120, 
        max_speed,
        90, 120, 140
    },
    {
        0,
        100, 250, 360,
        220,
        100, 250, 360
    }
};

#endif