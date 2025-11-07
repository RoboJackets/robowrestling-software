#ifndef POSITION_ENUM_H
#define POSITION_ENUM_H

//Positions for self and enemy
enum class Position {
    None,
    Left,
    Left_Middle,
    Left_Middle_Close,
    Middle_Close,
    Middle_Far,
    Right_Middle_Close,
    Right_Middle,
    Right,

    Flag_Left,
    Flag_Right,


    On_Line_Left,
    On_Line_Right,
    Off_Line,
    On_Line
};

#endif