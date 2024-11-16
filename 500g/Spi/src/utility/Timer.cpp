#include "Timer.h"

bool Timer::getReady() {
    return (currentTime - previousTime) >= timeInterval;
}

void Timer::setTimeInterval(int time) {
    timeInterval = time;  
}

void Timer::setCurrentTime(int time) {
    currentTime = time;  
}

void Timer::setPreviousTime(int time) {
    previousTime = time;
}