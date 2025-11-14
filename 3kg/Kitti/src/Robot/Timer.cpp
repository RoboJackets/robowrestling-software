#include "Robot/Timer.hpp"

Timer::Timer(unsigned long initial_time) {
    start_time = initial_time;
    duration = 0;
    global_time = initial_time;
    runningProcess = false;
}

void Timer::begin() {
    start_time = 0;
    global_time = 0;
    runningProcess = false;
}

void Timer::startTimer(unsigned long duration){
    this->duration = duration;
    start_time = global_time;
    runningProcess = true;
}

void Timer::updateTime() {
    global_time = global_time + 1;
    if (duration > 0) {
        duration = duration - 1;
    }
    if (runningProcess && duration == 0) {
        runningProcess = false;
    }
}

bool Timer::getRunningProcess() {
    return runningProcess;
}

int Timer::getDuration() {
    return duration;
}