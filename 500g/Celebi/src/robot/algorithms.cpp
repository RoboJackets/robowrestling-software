#include "robot/algorithms.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world, uint8_t* strategy, timer* draw_timer, timer *match_start_timer) {
    this->robot = robot;
    this->world = world;
    this->draw_timer = draw_timer;
    this->match_start_timer = match_start_timer;
    selfPosition = OFF;
    enemyPosition = UNKNOWN;
    states.match = SET_TIMER;
    states.circle = D_GO_STRAIGHT;
    states.attack = A_BLIND;
}

// main strategy function
//      attack_pattern: if there is an enemy seen, calls turn_towards, if enemy ahead, attack_forward
//          turn_towards: turns toward enemy if not ahead, returns 0 if enemy is straight ahead
//          attack_forward: attacks for 100 millis if enemy is ahead
//      draw_circle: runs if attack_pattern returns 0 (no enemy seen)
//          drives until line is seen, then backs off and turns, then coninues forward
void algorithms :: match_strategy() {
    // update positions
#ifdef PROFILING
    unsigned long start_time = micros();
#endif
    selfPosition = world->line_check();
    enemyPosition = world->enemy_pos();
#ifdef PROFILING
    algo_stats->process_sensors_time += micros() - start_time;
#endif
    // at beginning of round, drive forward for a bit
    if (*strategy != 0) {
        if (match_start() == 1) {
            return;
        }
    }

    if (attack_pattern() == 0) {
        draw_circle();
    }

}

//strategy will never be 0
//strategy can be 1, 2, 3 (swerve left), 4 (straight), 5, 6, 7 (swerve right)
int algorithms :: match_start() {

    if (states.match == SET_TIMER) {
        match_start_timer->set_action_timer(start_data.lengths[*strategy]);
        states.match = START;
    }
    if (match_start_timer->check_action_time()) {
        states.match = START_FINISHED;
    }
    if (states.match != START_FINISHED) {
        if (*strategy <= 3) {
            robot->drive_custom(start_data.powers[*strategy], max_speed, 1, 1);
        } else if (*strategy == 4) {
            robot->drive_forward(start_data.powers[*strategy]);
        } else {
            robot->drive_custom(max_speed, start_data.powers[*strategy], 1, 1);
        }
        return 1;
    }
    return 0;
}

// returns 0 if no enemy detected, otherwise 1
// turns toward enemy if not ahead
// attacks for 100 millis if enemy is ahead
int algorithms :: attack_pattern() {
#ifdef PROFILING
    unsigned long start_time = micros();
#endif
    // no enemy detected
    if (enemyPosition == UNKNOWN) {
#ifdef PROFILING
        algo_stats->attack_pattern_time += micros() - start_time;
#endif
        return 0;
    }
    // if already facing enemy, attack
    if (turn_towards() == 0) {
        attack_forward();
    }
#ifdef PROFILING
    algo_stats->attack_pattern_time += micros() - start_time;
#endif
    return 1;
}

#ifdef USE_DEBUG
void algorithms :: test() {
    // drive forward at constant speed
    robot->turn_left(50);
}
#endif

int algorithms :: draw_circle() {
    // state transition for backng off and turning away from line
    // check if the bot is currently backing off or turning after hitting a line
#ifdef PROFILING
    unsigned long start_time = micros();
#endif
    if (states.circle == D_GO_BACKWARDS && draw_timer->check_action_time()) {
        // finished backing off, start turning
        states.circle = D_TURN;
        robot->brake();
        draw_timer->set_action_timer(70);
#ifdef PROFILING
        algo_stats->draw_circle_time += micros() - start_time;
#endif
        return 0;
    } else if (states.circle == D_TURN && draw_timer->check_action_time()) {
        // finished turning, start going forwards again
        states.circle = D_GO_STRAIGHT;
        robot->brake();
#ifdef PROFILING
        algo_stats->draw_circle_time += micros() - start_time;
#endif
        return 0;
    }

    // action during each state
    // if the current state is going straight
    if (states.circle == D_GO_STRAIGHT) {
        //continue forward if no line detected
        if (selfPosition == OFF) {
            robot->drive_forward(60);
        //there is a line, set an action to go backwards
        } else {
            robot->brake();
            draw_timer->set_action_timer(100);
            states.circle = D_GO_BACKWARDS;
        }
    // if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot->drive_backward(max_speed);
    // if the current state is neither, turn to find enemy
    // this should never be reached
    } else {
        robot->turn_left(max_speed);
    }
#ifdef PROFILING
    algo_stats->draw_circle_time += micros() - start_time;
#endif
    return 0;
}

int algorithms :: draw_circle_edge() {
    // state transition for backng off and turning away from line
    // check if the bot is currently backing off or turning after hitting a line
    if (states.circle == D_GO_BACKWARDS && draw_timer->check_action_time()) {
        // finished backing off, start turning
        states.circle = D_TURN;
        robot->brake();
        draw_timer->set_action_timer(100);
        return 0;
    } else if (states.circle == D_TURN && draw_timer->check_action_time()) {
        // finished turning, start going forwards again
        states.circle = D_GO_STRAIGHT;
        robot->brake();
        return 0;
    }

    // action during each state
    // if the current state is going straight
    if (states.circle == D_GO_STRAIGHT) {
        //continue forward if no line detected
        if (selfPosition == OFF) {
            robot->drive_forward(60);
        //there is a line, set an action to go backwards
        } else {
            robot->brake();
            draw_timer->set_action_timer(50);
            states.circle = D_GO_BACKWARDS;
        }
    // if the current state is go backwards
    } else if (states.circle == D_GO_BACKWARDS) {
        robot->drive_backward(max_speed);
    // if the current state is neither, turn to find enemy
    // this should never be reached
    } else {
        robot->turn_left(max_speed);
    }
    return 0;
}


// drive forward if we see someone in front of us and return 1, otherwise return 0
// assume that we have already been confirmed to see
int algorithms :: attack_forward() {
#ifdef PROFILING
    unsigned long start_time = micros();
#endif
    enemy_states enemy = enemyPosition;
    //if the robot is close, drive forward fast
        //if the robot is close, drive forward fast
        if (enemy == CLOSE_MID) {
            robot->drive_forward(200);
#ifdef PROFILING
            algo_stats->attack_forward_time += micros() - start_time;
#endif
            return 1;
        //if the robot is a little further, drive forward slower
        } else if (enemy == FRONT) {
            robot->drive_forward(150);
#ifdef PROFILING
            algo_stats->attack_forward_time += micros() - start_time;
#endif
            return 1;
        } else if (enemy == CLOSE_MID_LEFT) {
            robot->drive_custom(120,200, 1, 1);
#ifdef PROFILING
            algo_stats->attack_forward_time += micros() - start_time;
#endif
            return 1;
        } else if (enemy == CLOSE_MID_RIGHT) {
            robot->drive_custom(200, 120, 1, 1);
#ifdef PROFILING
            algo_stats->attack_forward_time += micros() - start_time;
#endif
            return 1;
        //if we don't see the robot, brake and do nothing
        } else {
            robot->brake();
#ifdef PROFILING
            algo_stats->attack_forward_time += micros() - start_time;
#endif
            return 0;
        }
}


// returns 0 if we should proceed to attack_forward, returns 1 otherwise
// changes turn direction to last seen direction
int algorithms :: turn_towards() {
#ifdef PROFILING
    unsigned long start_time = micros();
#endif
    enemy_states enemy = enemyPosition;
    if(enemy == FRONT_LEFT) {
        //turn left a little slower
        robot->turn_left(med_turn);
#ifdef PROFILING
        algo_stats->turn_towards_time += micros() - start_time;
#endif
        return 1;
    } else if (enemy == LEFT) {
        //turn left
        robot->turn_left(fast_turn);
#ifdef PROFILING
        algo_stats->turn_towards_time += micros() - start_time;
#endif
        return 1;
    } else if (enemy == FRONT_RIGHT) {
        //turn right a little slower
        robot->turn_right(med_turn);
#ifdef PROFILING
        algo_stats->turn_towards_time += micros() - start_time;
#endif
        return 1;
    } else if (enemy == RIGHT) {
        //turn right
        robot->turn_right(fast_turn);
#ifdef PROFILING
        algo_stats->turn_towards_time += micros() - start_time;
#endif
        return 1;
    }
#ifdef PROFILING
    algo_stats->turn_towards_time += micros() - start_time;
#endif
    return 0;
}

#ifdef PROFILING
void algorithms:: add_stats(algorithm_stats* algo_stats) {
    this->algo_stats = algo_stats;
}
#endif