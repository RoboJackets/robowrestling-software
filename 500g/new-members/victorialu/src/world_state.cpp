#include "world_state.hpp"

world_state::world_state(int* ir, int* line) {
    ir_sensors = ir;
    line_sensors = line;
}

//use line_sensors array to decide where the robot is
line_states world_state::line_check() {
    
}

//use ir_sensors array to decide where the enemy is
enemy_states world_state::enemy_pos() {
    
}

//?
void world_state::clean() {

}


