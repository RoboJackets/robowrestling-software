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
    /**
     * General Strategy for the Match based on self_position and enemy_position.
     * 
     * Current tests on Joe's robot shows that robot cannot see after search with snake_search()
     * Flow Chart: Reset process durations. If enemy is front, attack. Otherwise, check lines. Then run queued process.
     * Default to snake_search() and do "crossing road" sweeps
     */

    // Resetting process durations
    Algos prev = InvalidAlgo;
    if (timer->getRunningProcess() == false) {
        prev = curr_algo;
        curr_algo = InvalidAlgo;
    }

    // Always attack first. Overrides the queue for algorithms
    if (enemy_position == Front) {
        if (timer->getRunningProcess() == false) {
            timer->startTimer(5);
        }
        curr_algo = CheckingAttack;
        attack_forward();
        return;
    }

    // Check priority items: attack and line control resolves first
    if (curr_algo == CheckingAttack) {
        attack_forward();
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
        return;
    } else if (self_position == TopRight) {
        curr_algo = LineRightAlgo;
        timer->startTimer(30);
        actions->drive_left(50);
        return;
    }
    
    // Check algos in queue
    if (curr_algo != InvalidAlgo) {
        // Searching algorithm with SnakeLeft, SnakeRight, SnakeForward
        if (curr_algo == SnakeLeft) {
            actions->drive_left(70);
        } else if (curr_algo == SnakeRight) {
            actions->drive_right(70);
        } else if (curr_algo == SnakeForward) {
            actions->drive_forward(70);
        }
    } else {
        // Selecting correct detection algorithm
        snake_search(prev);
    }
}

void Algorithms::update_algo_state(line_states self_pos, enemy_states enemy_pos) {
    self_position = self_pos;
    enemy_position = enemy_pos;
}

void Algorithms::snake_search(Algos prev) {
    // Snaking. Left for 7, right for 14, forward 10
    if (timer->getRunningProcess() != false) {
        // Another process is running. Quit out of this one
        return;
    }
    if (prev == SnakeLeft) {
        timer->startTimer(14);
        curr_algo = SnakeRight;
    } else if (prev == SnakeRight) {
        timer->startTimer(10);
        curr_algo = SnakeForward;
    } else {
        timer->startTimer(7);
        curr_algo = SnakeLeft;
    }
    
}

void Algorithms::attack_forward() {
    // Implement attack forward logic
    // TODO: Curve towards enemy if you want
    actions->drive_forward(170); 
}




// Currently doing nothing. Implement for more timer control
// void Algorithms::adv_line_movement() {
//     // Algorithm for setting timer for precise line movement
//     if (timer->getRunningProcess() == false) {
//         timer->startTimer(500);
//     }

//     curr_algo = LineAdvAlgo;
//     if (self_position == TopLeft) {
//         actions->drive_right(100);

//     } else if (self_position == TopRight) {
//         actions->drive_left(100);
//     } else {
//         actions->drive_forward(70);
//     }
// }
