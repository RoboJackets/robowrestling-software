#include "algorithms/Tracker.hpp"

Tracker::Tracker(WorldState *_worldState, RobotAction* _robotAction, int _mode) {
    worldState = _worldState;
    robotAction = _robotAction;
    previousAction = nullptr;
    previousPosition = Position::None;
    acceleration = 0;
    leftAcceleration = 0;
    rightAcceleration = 0;
    mode = _mode;
    stuck = false;
    turnt = false;
    accelerationTimer = new AutoTimer(ACCELERATION_TIMER_DURATION);
    backupTimer = new AutoTimer(BACKUP_TIMER_DURATION);
    brakeTimer = new AutoTimer(BRAKE_TIMER_DURATION);
    stuckTimer = new AutoTimer(STUCK_TIMER_DURATION);
    backSpinLeft = new BackSpin(robotAction, true);
    backSpinRight = new BackSpin(robotAction, false);
    _scan = new Scan(robotAction);
    turnAround = new TurnAround(robotAction);
}

void Tracker::run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Both || position == Position::On_Line_Right) {
        backSpinRight->resetAction();
        backSpinRight->run();
        previousAction = backSpinRight;
        worldState->overrideLastPosition(Position::None);
    }
    if (position == Position::On_Line_Left) {
        backSpinLeft->resetAction();
        backSpinLeft->run();
        previousAction = backSpinLeft;
        worldState->overrideLastPosition(Position::None);
    }
    if (position == Position::Off_Line) {
        if (stuck) {
            if (!brakeTimer->getReady()) {
                robotAction->brake();
            } else {
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
    if (true) {
        if (previousPosition == enemyPosition) {
            if (stuckTimer->getReady()) {
                stuck = true;
                backupTimer->resetTimer();
                brakeTimer->resetTimer();
            }
        } else {
            stuckTimer->resetTimer();
            worldState->overrideLastPosition(Position::None);
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
        int rightSpeed = MAX_SAFE_SPEED + leftAcceleration;
        if (accelerationTimer->getReady()) { 
            if (rightSpeed < MAX_SPEED) {
                leftAcceleration++;
            } 
            accelerationTimer->resetTimer();
        }
        robotAction->turn(SLOW_SPEED, rightSpeed);
    } else {
        leftAcceleration = 0;
    }
    if (enemyPosition == Position::Right) {
        int leftSpeed = rightAcceleration + MAX_SAFE_SPEED;
        if (accelerationTimer->getReady()) { 
            if (leftSpeed < MAX_SPEED) {
                rightAcceleration++;
            }
            accelerationTimer->resetTimer();  
        }
        robotAction->turn(leftSpeed, SLOW_SPEED);
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
        robotAction->turn(SLOW_SPEED, MAX_SAFE_SPEED);
    }
    if (lastSeen == Position::Right) {
        robotAction->turn(MAX_SAFE_SPEED, SLOW_SPEED);
    }
    if (lastSeen == Position::None) {
        default_action();
    }
}

void Tracker::default_action() {
    if (mode == 0) { robotAction->forward(MAX_SAFE_SPEED); }
    if (mode == 1) { _scan->run(); }
    if (mode == 2) { 
        turnAround->run();
        if (!turnt) {
            turnt = true;
        } else if (turnAround->getActionCompleted()) {
            mode = 0;
        } 
    }
}