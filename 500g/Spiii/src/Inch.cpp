#include "Inch.hpp"

Inch::Inch(WorldState* _worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
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
    SelfPositionEnum selfPosition = worldState->getPosition();
    OpponentPositionEnum enemyPosition = worldState->getEnemyPosition();
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
        robotAction->forward(SPEED);
        brakeTimer->resetTimer();
    } else if (!brakeTimer->isReady()) {
        robotAction->brake();
    } else {
        inchTimer->resetTimer();
        brakeTimer->resetTimer();
    }
    return completed;
}