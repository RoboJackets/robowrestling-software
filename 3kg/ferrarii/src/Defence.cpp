#include "Defence.hpp"

Defence::Defence(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    notSeenTimer = new Timer(NOT_SEEN_TIMER_DURATION);
    backupTimer = new Timer(BACKUP_TIMER_DURATION);
    spinTimer = new Timer(SPIN_TIMER_DURATION);
    inchTimer = new Timer(INCH_TIMER_DURATION);
    stopTimer = new Timer(STOP_TIMER_DURATION);
    dashTimer = new Timer(DASH_TIMER_DURATION);
    has_dashed = false;
    lastState = NONE;
}

void Defence::run() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (selfPosition != NOT_ON_LINE) {
        onLine();
    } else if (!backupTimer->isReady()) {
        robotActions->backward(MODERATE_SPEED);
    } else if (!spinTimer->isReady()) {
        robotActions->spinLeft(MODERATE_SPEED);
    } else {
        opponentInSight();
    }
}

void Defence::opponentInSight() {
    OpponentPositionEnum enemyPosition = worldState->getOpponentPosition();
    if (enemyPosition == NOT_SEEN) {
        opponentLastKnownLocation();
    } else {
        notSeenTimer->resetTimer();
    }
    if (enemyPosition == FRONT_CLOSE) {
        robotActions->forward(MAX_SPEED);
    }
    else if (enemyPosition == REALLY_CLOSE_LEFT) {
        robotActions->turnForward(REALLY_FAST_SPEED, MAX_SPEED);
    }
    else if (enemyPosition == REALLY_CLOSE_RIGHT) {
        robotActions->turnForward(MAX_SPEED, REALLY_FAST_SPEED);
    }
    else if (enemyPosition == FRONT_FAR) {
        opponentLocationUnknown();
    }
    else if (enemyPosition == CLOSE_LEFT) {
        robotActions->spinLeft(VERY_SLOW_SPEED);
    }
    else if (enemyPosition == CLOSE_RIGHT) {
        robotActions->spinRight(VERY_SLOW_SPEED);
    }
    else if (enemyPosition == MID_LEFT) {
        robotActions->spinLeft(KINDA_SLOW_SPEED);
    }
    else if (enemyPosition == MID_RIGHT) {
        robotActions->spinRight(KINDA_SLOW_SPEED);
    }
    else if (enemyPosition == FAR_LEFT) {
        robotActions->spinLeft(SLOW_SPEED);
    }
    else if (enemyPosition == FAR_RIGHT) {
        robotActions->spinRight(SLOW_SPEED);
    }
    else if (enemyPosition == BEHIND) {
        robotActions->spinLeft(SLOW_SPEED);
    }
}

void Defence::opponentLastKnownLocation() {
    OpponentPositionEnum lastEnemyPosition = worldState->getLastOpponentPosition();
    if (notSeenTimer->isReady()) {
        worldState->clearOpponentPosition();
    }
    if (lastEnemyPosition == NOT_SEEN) {
        opponentLocationUnknown();
    }
}

void Defence::opponentLocationUnknown() {
    if (!inchTimer->isReady()) {
        robotActions->forward(SAFE_SPEED);
    } else if (!stopTimer->isReady()) {
        robotActions->brake();
    } else {
        inchTimer->resetTimer();
        stopTimer->resetTimer();
    }
}

void Defence::onLine() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (selfPosition == ON_LINE_BOTTOM_LEFT) {
        robotActions->forward(FAST_SPEED);
    }
    if (selfPosition == ON_LINE_BOTTOM_RIGHT) {
        robotActions->forward(FAST_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_LEFT) {
        backupTimer->resetTimer();
        spinTimer->resetTimer();
        robotActions->backward(FAST_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_RIGHT) {
        backupTimer->resetTimer();
        spinTimer->resetTimer();
        robotActions->backward(FAST_SPEED);
    }
}

