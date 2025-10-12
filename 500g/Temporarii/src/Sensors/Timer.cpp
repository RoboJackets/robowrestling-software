/*
* From Celebi program implementations
*/
#include "Sensors/Timer.hpp"

Timer::Timer(unsigned long initial_time) {
    this->match_start = initial_time;
    this->action_start = initial_time;
    this->current_time = initial_time;
    this->timer_state = false;
}

void Timer::update_time(unsigned long new_time) {
    current_time = new_time;
}

// return true if the timer has expired
bool Timer::check_action_time() {
    bool checkup = current_time - action_start >= action_length;
    if (checkup) {
        timer_state = false;
    }
    return checkup;
}

unsigned long Timer::check_match_time() {
    return current_time - match_start;
}

void Timer::set_action_timer(unsigned long length) {
    timer_state = true;
    action_length = length;
    action_start = current_time;
}

unsigned long Timer::get_action_start() {
    return action_start;
}

unsigned long Timer::get_current_time() {
    return current_time;
}

bool Timer::get_timer_state() {
    return timer_state;
}