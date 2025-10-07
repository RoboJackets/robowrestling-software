#include "algorithms/Tracker.hpp"

Tracker::Tracker(WorldState *_worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    previousAction = nullptr;
    previousPosition = Position::None;
    acceleration = 0;
    leftAcceleration = 0;
    rightAcceleration = 0;
    stuck = false;
    accelerationTimer = new AutoTimer(ACCELERATION_TIMER_DURATION);
    backupTimer = new AutoTimer(BACKUP_TIMER_DURATION);
    brakeTimer = new AutoTimer(BRAKE_TIMER_DURATION);
    stuckTimer = new AutoTimer(STUCK_TIMER_DURATION);
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
        if (stuck) {
            if (!brakeTimer->getReady()) {
                robotAction->brake();
            } else {
                Position enemyPosition = worldState->getEnemyPosition();
                if (previousPosition == enemyPosition) {
                    backupTimer->resetTimer();
                }
                robotAction->back(MAX_SPEED);
                if (backupTimer->getReady()) {
                    stuck = false;
                    stuckTimer->resetTimer();
                }
            }
        }
        else if (previousAction == nullptr || previousAction->getActionCompleted()) 
        { 
            track(); 
        }
        else { previousAction->run(); }
    }
}

void Tracker::track() {
    Position enemyPosition = worldState->getEnemyPosition();
    if (previousPosition != Position::None) {
        if (previousPosition == enemyPosition) {
            if (stuckTimer->getReady()) {
                stuck = true;
                backupTimer->resetTimer();
                brakeTimer->resetTimer();
            }
        } else {
            stuckTimer->resetTimer();
        }
    }
    previousPosition = enemyPosition;
    if (enemyPosition == Position::Middle_Close) {
        robotAction->forward(MAX_SPEED);
    }
    if (enemyPosition == Position::Middle_Far) {
        if (accelerationTimer->getReady()) { 
            if (acceleration + MAX_SAFE_SPEED < MAX_SPEED) {
                acceleration++;
            }
            accelerationTimer->resetTimer();
        }
        robotAction->forward(MAX_SAFE_SPEED + acceleration);
    } else {
        acceleration = 0;
    }
    if (enemyPosition == Position::Left) {
        if (accelerationTimer->getReady()) { 
            if (leftAcceleration + MAX_SAFE_SPEED < MAX_SPEED) {
                leftAcceleration++;
            } 
            accelerationTimer->resetTimer();
        }
        robotAction->turn(MAX_SAFE_SPEED + leftAcceleration, MODERATE_SPEED);
    } else {
        leftAcceleration = 0;
    }
    if (enemyPosition == Position::Right) {
        if (accelerationTimer->getReady()) { 
            if (rightAcceleration + MAX_SAFE_SPEED < MAX_SPEED) {
                rightAcceleration++;
            }
            accelerationTimer->resetTimer();  
        }
        robotAction->turn(MODERATE_SPEED, MAX_SAFE_SPEED + rightAcceleration);
    } else {
        rightAcceleration = 0;
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