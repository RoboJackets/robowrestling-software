#include "Inch.hpp"

Inch::Inch(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    inchTimer = new Timer(INCH_DURATION);
    brakeTimer = new Timer(BRAKE_DURATION);
    cutoffTimer = new Timer(CUTOFF_DURATION);
    completed = false;
    started = false;
}

bool Inch::run() {
    if (completed) {
        return completed;
    }
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    OpponentPositionEnum enemyPosition = worldState->getOpponentPosition();
    if (selfPosition != NOT_ON_LINE) {
        completed = true;
        return completed;
    }
    if (enemyPosition != NOT_SEEN) {
        completed = true;
        return completed;
    }
    if (!started) {
        started = true;
        inchTimer->resetTimer();
        brakeTimer->resetTimer();
        cutoffTimer->resetTimer();
    }
    if (cutoffTimer->isReady()) {
        completed = true;
    }
    if (!inchTimer->isReady()) {
        robotActions->forward(SPEED);
        brakeTimer->resetTimer();
    } else if (!brakeTimer->isReady()) {
        robotActions->brake();
    } else {
        inchTimer->resetTimer();
        brakeTimer->resetTimer();
    }
    return completed;
}