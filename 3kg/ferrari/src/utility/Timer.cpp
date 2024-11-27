#include "utility/Timer.hpp"

Timer::Timer(int duration, int *currentTimePointer) {
    alertTime = duration;
    currentTime = currentTimePointer;
}

bool Timer::getReady() {
    return *currentTime > alertTime;
}

void Timer::executeOnReady(void (* function)()) {
    if (getReady()) {
        function();
    }
}