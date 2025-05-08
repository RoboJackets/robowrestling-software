#include "utility/AutoTimer.hpp"


AutoTimer::AutoTimer(int _timerlength) {
    timerlength = _timerlength;
    startTime = millis();
}

bool AutoTimer::getReady() {
    return ((millis() - startTime) > timerlength);
}

void AutoTimer::resetTimer() {
    startTime = millis();
}
