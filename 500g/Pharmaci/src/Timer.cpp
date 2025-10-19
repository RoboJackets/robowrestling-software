#include "Timer.h"
#include <Arduino.h>  // for uint32_t on some cores (optional)

bool Timer::getReady() {
    return (uint32_t)(currentTime - previousTime) >= timeInterval;  // rollover-safe
}

void Timer::setTimeInterval(uint32_t time) { timeInterval = time; }
void Timer::setCurrentTime(uint32_t time)   { currentTime = time; }
void Timer::setPreviousTime(uint32_t time)  { previousTime = time; }
