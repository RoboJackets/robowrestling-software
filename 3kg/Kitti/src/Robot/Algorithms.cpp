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

    // Always attack first
    if (enemy_position == Front) {
        if (timer->getRunningProcess() == false) {
            timer->startTimer(5);
        }
        curr_algo = CheckingAttack;
        attack_forward();
        return;
    }

    // Set current state
    if (timer->getRunningProcess() == false) {
        if (curr_algo == SnakeLeft || curr_algo == SnakeRight || curr_algo == SnakeForward) {
            slammy_whammy();
        } else {
            curr_algo = InvalidAlgo;
        }
    }

    // Special Case Algo: Line Check -> Check before traditional line check bc line check baked into algo
    if (curr_algo == CheckingAttack) {
        attack_forward();
        return;
    } else if (curr_algo == LineAdvAlgo) {
        adv_line_movement();
        return;
    } else if (curr_algo == LineRightAlgo) {
        // Finish out turns
        if (timer->getDuration() > 10) {
            actions->drive_left(50);
        } else {
            actions->drive_forward(50);
        }
        return;
    } else if (curr_algo == LineLeftAlgo) {
        // Finish out turns
        if (timer->getDuration() > 10) {
            actions->drive_right(50);
        } else {
            actions->drive_forward(50);
        }
        return;
    }

    // Line Check
    if (self_position == TopLeft) {
        curr_algo = LineLeftAlgo;
        timer->startTimer(30);
        actions->drive_right(50);
    } else if (self_position == TopRight) {
        curr_algo = LineRightAlgo;
        timer->startTimer(30);
        actions->drive_left(50);
    } else if (curr_algo != InvalidAlgo) {
        // Checking queued algo
        if (curr_algo == SnakeLeft) {
            actions->drive_left(70);
        } else if (curr_algo == SnakeRight) {
            actions->drive_right(70);
        } else {
            actions->drive_forward(70);
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
    // } else if (enemy_position == Left) {
    //     // Set timer to move forwards for the dodge before curving towards the enemy
    // } else if (enemy_position == Right) {
    //     // Same thing for right
    } else {
        // Snaking
        if (curr_algo == SnakeLeft) {
            if (timer->getRunningProcess() == false) {
                timer->startTimer(14);
            }
            curr_algo = SnakeRight;
        } else if (curr_algo == SnakeRight) {
            if (timer->getRunningProcess() == false) {
                timer->startTimer(14);
            }
            curr_algo = SnakeForward;
        } else {
            if (timer->getRunningProcess() == false) {
                timer->startTimer(7);
            }
            curr_algo = SnakeLeft;
        }
    }
    
}

void Algorithms::attack_forward() {
    // Implement attack forward logic
    actions->drive_forward(170); 
}

// Currently doing nothing. Implement for more timer control
void Algorithms::adv_line_movement() {
    // Algorithm for setting timer for precise line movement
    if (timer->getRunningProcess() == false) {
        timer->startTimer(500);
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
