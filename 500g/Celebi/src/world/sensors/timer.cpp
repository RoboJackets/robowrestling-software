#include "world/sensors/timer.hpp"

timer :: timer(unsigned long initial_time) {
    this -> action_start = initial_time;
    this -> current_time = initial_time;
    this -> timer_state = false;
    this -> action_length = 0;
}


void timer :: update_time(unsigned long new_time) {
    current_time = new_time;
}

//return true if the timer has expired
bool timer :: check_action_time() {
    if (timer_state == false) {
        return 0;
    } 
    bool checkup = current_time - action_start >= action_length;
    if (checkup) {
        timer_state = false;
    }
    return checkup;
}

void timer :: set_action_timer(unsigned long length) {
    timer_state = true;
    action_length = length;
    action_start = current_time;
}

unsigned long timer :: get_action_start() {
    return action_start;
}

unsigned long timer :: get_current_time() {
    return current_time;
}

bool timer :: get_timer_state() {
    return timer_state;
}

void timer :: set_stopwatch() {
    action_start = current_time;
}

unsigned long timer :: check_stopwatch() {
    return current_time - action_start;
}