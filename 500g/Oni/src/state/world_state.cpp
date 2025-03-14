#include "state/world_state.h"

world_state :: world_state(LINESENSOR * line_left, LINESENSOR * line_right, IRSENSOR * ir_middle, IRSENSOR * ir_middle_left, IRSENSOR * ir_middle_right){
    this -> line_left = line_left;
    this -> line_right = line_right;
    this -> ir_middle = ir_middle;
    this -> ir_middle_left = ir_middle_left;
    this -> ir_middle_right = ir_middle_right;
}

SelfPosition world_state:: line_state(){
    int left_value = line_left->getValue();
    int right_value = line_right->getValue();

    if (left_value > 500 || right_value > 500){
        return OFF_LINE;
    }
    else if (left_value <= 500 || right_value <= 500){
        return ON_LINE;
    }

}

EnemyPosition world_state:: enemy_location(){
    bool mid_val = ir_middle->getValue();
    bool mid_left_val = ir_middle_left->getValue();
    bool mid_right_val = ir_middle_right->getValue();

    if (mid_val){
        return MIDDLE;
    }
    else if (mid_right_val){
        return RIGHT;
    }
    else if (mid_left_val){
        return LEFT;
    } else {
        return NOTHING;
    }

}