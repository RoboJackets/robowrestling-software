#include "Timer.hpp"

Timer::Timer(unsigned long _duration, bool startActivated = false) {
    duration = _duration;
    activated = false;
    targetTime = 0;
    if (startActivated) {
        activated = true;
    }
}

bool Timer::isReady() {
    currentTime = millis();
    if (activated == false) {
        targetTime = millis() + duration;
        activated = true;
    }
    if (targetTime < currentTime) {
        return true;
    } else {
        return false;
    }
}

void Timer::resetTimer() {
    activated = false;
}