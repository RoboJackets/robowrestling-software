#include "World_State.hpp"



World_State::World_State(int* lineSensors, int* irSensors) {
    this->lineSensors = lineSensors;
    this->irSensors = irSensors;
 
}


void World_State::checkConcurrency() {
    for (int i = 0; i < 3; i++) {
        if (irSensors[i] == 1) {
            concurrency[i]++;

        } else {
            concurrency[i] = 0;
        }
        if(concurrency[i]>= 10){
            irSensors[i] = 1;
        }
        else{
            irSensors[i] = 0;
        }
    }
}

// World_State::line_check() {
//     if (lineSensors[0] == 1 && lineSensors[1] == 1) return CENTER;
//     if (lineSensors[0] == 1) return LEFT;
//     if (lineSensors[1] == 1) return RIGHT;
//     return OFF_LINE;
// }

//  World_State::enemy_pos() {
//     if (irSensors[1] == 1) return FRONT;
//     if (irSensors[0] == 1) return LEFT;
//     if (irSensors[2] == 1) return EnemyState.RIGHT;
//     return NONE;
// }
