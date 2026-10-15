#include "utility/AutoTimer.hpp"


AutoTimer::AutoTimer(int _timerlength) {
    timerlength = _timerlength;
    started = false;
    startTime = millis();
}

bool AutoTimer::getReady() {
    if (!started) {
        startTime = millis();
        started = true;
    }
    return ((int)(millis() - startTime) > timerlength);
}

void AutoTimer::resetTimer() {
    startTime = millis();
    started = false;
}
