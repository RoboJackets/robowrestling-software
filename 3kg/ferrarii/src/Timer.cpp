#include "Timer.hpp"

Timer::Timer(unsigned long _duration, bool startActivated = false) {
    duration = _duration;
    targetTime = millis() + duration;
}

bool Timer::isReady() {
    return millis() >= targetTime;
}

void Timer::resetTimer() {
    targetTime = millis() + duration;
}