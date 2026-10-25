#include "timer.hpp"

timer::timer(long* currentMillis) {
    this->currentMillis = currentMillis;
    startMillis = 0;
    endMillis = 0;
    targetMillis = 0;
    running = false;
}

void timer::start() {
    if (!running) {
        startMillis = *currentMillis;
        running = true;
    }
}

void timer::stop() {
    if (running) {
        endMillis = *currentMillis;
        running = false;
    }
}

void timer::reset() {
    startMillis = 0;
    endMillis = 0;
    targetMillis = 0;
    running = false;
}

void timer::setTarget(long target) {
    targetMillis = target;
}

long timer::elapsedMilliseconds() {
    return running ? (*currentMillis - startMillis) : (endMillis - startMillis);
}

bool timer::isRunning() {
    return running;
}

bool timer::isFinished() {
    long elapsed = running ? (*currentMillis - startMillis) : (endMillis - startMillis);
    return elapsed >= targetMillis;
}