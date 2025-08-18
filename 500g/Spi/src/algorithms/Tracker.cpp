#include "algorithms/Tracker.hpp"

Tracker::Tracker(WorldState *_worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    previousAction = nullptr;
    acceleration = 0;
    accelerationTimer = new AutoTimer(ACCELERATION_TIMER_DURATION);
    backSpinLeft = new BackSpin(robotAction, true);
    backSpinRight = new BackSpin(robotAction, false);
    _scan = new Scan(robotAction);
}

void Tracker::run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Both || position == Position::On_Line_Right) {
        backSpinRight->resetAction();
        backSpinRight->run();
        previousAction = backSpinRight;
    }
    if (position == Position::On_Line_Left) {
        backSpinLeft->resetAction();
        backSpinLeft->run();
        previousAction = backSpinLeft;
    }
    if (position == Position::Off_Line) {
        if (previousAction == nullptr || previousAction->getActionCompleted()) 
        { 
            track(); 
        }
        else { previousAction->run(); }
    }
}

void Tracker::track() {
    Position enemyPosition = worldState->getEnemyPosition();
    if (enemyPosition == Position::Middle_Close) {
        robotAction->forward(MAX_SPEED);
    }
    if (enemyPosition == Position::Middle_Far) {
        if (accelerationTimer->getReady()) { 
            acceleration = acceleration + MAX_SAFE_SPEED == MAX_SPEED ? acceleration : acceleration + 1; 
        } else {
            accelerationTimer->resetTimer(); 
        }
        robotAction->forward(MAX_SAFE_SPEED + acceleration);
    } else {
        acceleration = 0;
    }
    if (enemyPosition == Position::Left) {
        robotAction->turn(MAX_SAFE_SPEED, MODERATE_SPEED);
    }
    if (enemyPosition == Position::Right) {
        robotAction->turn(MODERATE_SPEED, MAX_SAFE_SPEED);
    }
    if (enemyPosition == Position::None) {
        seek();
    }
}

void Tracker::seek() {
    Position lastSeen = worldState->getLastEnemyPosition();
    if (lastSeen == Position::Middle_Close) {
        robotAction->forward(MAX_SAFE_SPEED);
    }
    if (lastSeen == Position::Middle_Far) {
        robotAction->forward(MAX_SAFE_SPEED);
    }
    if (lastSeen == Position::Left) {
        robotAction->spinLeft(MAX_SAFE_SPEED);
    }
    if (lastSeen == Position::Right) {
        robotAction->spinRight(MAX_SAFE_SPEED);
    }
    if (lastSeen == Position::None) {
        scan();
    }
}

void Tracker::scan() {
    _scan->run();
}