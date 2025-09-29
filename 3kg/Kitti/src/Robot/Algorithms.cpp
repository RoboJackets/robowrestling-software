#include "Robot/Algorithms.hpp"

Algorithms::Algorithms(RobotActions* new_action, WorldState* new_state, Timer* timer, line_states self_pos, enemy_states enemy_pos) {
    actions = new_action;
    world_state = new_state;
    this->timer = timer;
    self_position = self_pos;
    enemy_position = enemy_pos;
    curr_algo = InvalidAlgo;
}

void Algorithms::match_strategy() {
    // General Strategy for the Match based on self_position and enemy_position
    // attack_forward();
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

    // Flow Chart: Line Check First -> Some algo running from being in queue -> Other algorithms

    // Set current state
    if (timer->getRunningProcess() == false) {
        curr_algo = InvalidAlgo;
    }

    // Special Case Algo: Line Check -> Check before traditional line check bc line check baked into algo
    if (curr_algo == LineAdvAlgo) {
        adv_line_movement();
        return;
    } else if (curr_algo == LineRightAlgo) {
        // Finish out turns
        actions->drive_right(100);
    } else if (curr_algo == LineLeftAlgo) {
        // Finish out turns
        actions->drive_left(100);
    }

    // Line Check
    if (self_position == TopLeft) {
        curr_algo = LineLeftAlgo;
        timer->startTimer(5);
        actions->drive_right(50);
    } else if (self_position == TopRight) {
        curr_algo = LineRightAlgo;
        timer->startTimer(5);
        actions->drive_left(50);
    } else if (curr_algo != InvalidAlgo) {
        // Checking queued algo
        if (curr_algo == SlammyWhammyAlgo) {
            slammy_whammy();
        }

    } else {
        // TODO: Select algo to run
        slammy_whammy();
    }
}

void Algorithms::update_algo_state(line_states self_pos, enemy_states enemy_pos) {
    self_position = self_pos;
    enemy_position = enemy_pos;
}

void Algorithms::slammy_whammy() {
    // Implement slammy whammy logic
    if (enemy_position == Front) {
        attack_forward();
    } else if (enemy_position == Left) {
        // Set timer to move forwards for the dodge before curving towards the enemy
    } else if (enemy_position == Right) {
        // Same thing for right
    } else {
        actions->drive_left(70);
    }
    
}

void Algorithms::attack_forward() {
    // Implement attack forward logic
    actions->drive_forward(170); 
}

void Algorithms::adv_line_movement() {
    // Algorithm for setting timer for precise line movement
    if (timer->getRunningProcess() == false) {
        timer->startTimer(50);
    }

    curr_algo = LineAdvAlgo;
    if (self_position == TopLeft) {
        actions->drive_right(100);
    } else if (self_position == TopRight) {
        actions->drive_left(100);
    } else {
        actions->drive_forward(70);
    }
}
