#include "world/sensors/timer.hpp"

timer :: timer(int initial_time) {
    this -> match_start = initial_time;
    this -> action_start = initial_time;
    this -> current_time = initial_time;
    this -> timer_set = false;
}


void timer :: update_time(int new_time) {
    current_time = new_time;
}

//return true if the timer has expired
bool timer :: check_action_time() {
    timer_set = current_time - action_start >= action_length;
    return timer_set;
}

int timer :: check_match_time() {
    return current_time - match_start;
}

void timer :: set_action_timer(int length) {
    action_length = length;
    action_start = current_time;
}

int timer :: get_action_start() {
    return action_start;
}

int timer :: get_current_time() {
    return current_time;
}