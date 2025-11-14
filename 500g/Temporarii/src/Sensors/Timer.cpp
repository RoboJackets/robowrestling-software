#include "Sensors/Timer.hpp"

Timer::Timer() {
    start_time = 0;
    duration_ms = 0;
    runningProcess = false;
}

Timer::Timer(unsigned long initial_time) {
    start_time = initial_time;
    duration_ms = 0;
    runningProcess = false;
}

void Timer::begin() {
    runningProcess = false;
    start_time = 0;
    duration_ms = 0;
}

void Timer::startTimer(unsigned long duration_ms) {
    this->duration_ms = duration_ms;
    start_time = millis();
    runningProcess = true;
}

void Timer::updateTime() {
    if (!runningProcess) return;

    unsigned long elapsed = millis() - start_time;
    if (elapsed >= duration_ms) {
        runningProcess = false; // Timer expired
    }
}

bool Timer::getRunningProcess() {
    return runningProcess;
}

unsigned long Timer::getDuration() {
    if (!runningProcess) return 0;

    unsigned long elapsed = millis() - start_time;
    if (elapsed >= duration_ms) return 0;

    return duration_ms - elapsed; // Remaining ms
}
