#include "utility/Timer.hpp"

Timer::Timer(int timerDuration, int *currentTimePointer) {
    duration = duration;
    alertTime = 0;
    startTime = 0;
    currentTime = currentTimePointer;
}

bool Timer::getReady() {
    return *currentTime > alertTime;
}

void Timer::setStartTime(int time) {
    startTime = time;
    alertTime = startTime + duration;
}

void Timer::executeOnReady(void (* function)()) {
    if (getReady()) {
        function();
    }
}