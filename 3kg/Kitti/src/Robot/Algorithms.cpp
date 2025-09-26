#include "Robot/Algorithms.hpp"

Algorithms::Algorithms(RobotActions* new_action, WorldState* new_state, line_states self_pos, enemy_states enemy_pos) {
    actions = new_action;
    world_state = new_state;
    self_position = self_pos;
    enemy_position = enemy_pos;
}

void Algorithms::match_strategy() {
    // General Strategy for the Match based on self_position and enemy_position
    attack_forward();
    // if (self_position == NoneLine) {
    //     actions->brake();
    // } else if (enemy_position == Front) {
    //     attack_forward();
    // } else if (enemy_position == Left) {
    //     actions->drive_left(100);
    // } else if (enemy_position == Right) {
    //     actions->drive_right(100);
    // } else if (enemy_position == Back) {
    //     actions->drive_backward(100);
    // } else {
    //     slammy_whammy();
    // }
}

void Algorithms::slammy_whammy() {
    // Implement slammy whammy logic
}

void Algorithms::attack_forward() {
    // Implement attack forward logic
    actions->drive_forward(100); 
}
