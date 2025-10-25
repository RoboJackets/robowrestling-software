#include "Strat.hpp"

Strat::Strat(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    notSeenTimer = new Timer(NOT_SEEN_TIMER_DURATION);
    backupTimer = new Timer(BACKUP_TIMER_DURATION, true);
    spinTimer = new Timer(SPIN_TIMER_DURATION, true);
    inchTimer = new Timer(INCH_TIMER_DURATION);
    stopTimer = new Timer(STOP_TIMER_DURATION);
}

void Strat::run() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (selfPosition != NOT_ON_LINE) {
        onLine();
        backupTimer->resetTimer();
        spinTimer->resetTimer();
    } else if (!backupTimer->isReady()) {
        robotActions->backward(MAX_SPEED);
    } else if (!spinTimer->isReady()) {
        robotActions->spinLeft(MAX_SPEED);
    } else {
        opponentInSight();
    }
}

void Strat::opponentInSight() {
    OpponentPositionEnum enemyPosition = worldState->getOpponentPosition();
    if (enemyPosition == NOT_SEEN) {
        opponentLastKnownLocation();
        return;
    }
    notSeenTimer->resetTimer();
    if (enemyPosition == FRONT_CLOSE) {
        robotActions->forward(MAX_SPEED);
    }
    if (enemyPosition == FRONT_FAR) {
        robotActions->forward(FAST_SPEED);
    }
    if (enemyPosition == CLOSE_LEFT) {
        robotActions->turnForward(SAFE_SPEED, FAST_SPEED);
    }
    if (enemyPosition == CLOSE_RIGHT) {
        robotActions->turnForward(FAST_SPEED, SAFE_SPEED);
    }
    if (enemyPosition == MID_LEFT) {
        robotActions->turnForward(SLOW_SPEED, FAST_SPEED);            
    }
    if (enemyPosition == MID_RIGHT) {
        robotActions->turnForward(FAST_SPEED, SLOW_SPEED);            
    }
    if (enemyPosition == FAR_LEFT) {
        robotActions->spinLeft(FAST_SPEED);
    }
    if (enemyPosition == FAR_RIGHT) {
        robotActions->spinRight(FAST_SPEED);
    }
    if (enemyPosition == BEHIND) {
        robotActions->spinLeft(MAX_SPEED);
    }
}

void Strat::opponentLastKnownLocation() {
    OpponentPositionEnum lastEnemyPosition = worldState->getLastOpponentPosition();
    if (notSeenTimer->isReady()) {
        worldState->clearOpponentPosition();
    }
    if (lastEnemyPosition == NOT_SEEN) {
        opponentLocationUnknown();
    }
    if (lastEnemyPosition == FRONT_CLOSE) {
        robotActions->forward(SAFE_SPEED);
    }
    if (lastEnemyPosition == FRONT_FAR) {
        robotActions->forward(SAFE_SPEED);
    }
    if (lastEnemyPosition == CLOSE_LEFT) {
        robotActions->turnForward(SLOW_SPEED, SAFE_SPEED);
    }
    if (lastEnemyPosition == CLOSE_RIGHT) {
        robotActions->turnForward(SAFE_SPEED, SLOW_SPEED);
    }
    if (lastEnemyPosition == MID_LEFT) {
        robotActions->turnForward(SLOW_SPEED, SAFE_SPEED);            
    }
    if (lastEnemyPosition == MID_RIGHT) {
        robotActions->turnForward(SAFE_SPEED, SLOW_SPEED);            
    }
    if (lastEnemyPosition == FAR_LEFT) {
        robotActions->spinLeft(SAFE_SPEED);
    }
    if (lastEnemyPosition == FAR_RIGHT) {
        robotActions->spinRight(SAFE_SPEED);
    }
    if (lastEnemyPosition == BEHIND) {
        robotActions->spinLeft(SAFE_SPEED);
    }
}

void Strat::opponentLocationUnknown() {
    if (!inchTimer->isReady()) {
        robotActions->forward(SAFE_SPEED);
    } else if (!stopTimer->isReady()) {
        robotActions->brake();
    } else {
        inchTimer->resetTimer();
        stopTimer->resetTimer();
    }
}

void Strat::onLine() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (selfPosition == ON_LINE_BOTTOM_LEFT) {
        robotActions->forward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_BOTTOM_RIGHT) {
        robotActions->forward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_LEFT) {
        backupTimer->resetTimer();
        spinTimer->resetTimer();
        robotActions->backward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_RIGHT) {
        backupTimer->resetTimer();
        spinTimer->resetTimer();
        robotActions->backward(MAX_SPEED);
    }
}

