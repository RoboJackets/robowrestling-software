#include "algorithms/InchForward.hpp"

/**
 * 250 ms moving
 * 250 ms stopped 
 */
InchForward::InchForward(WorldState *_worldState, RobotAction *_robotAction, int _speed) {
    moving = new AutoTimer(250);
    stopped = new AutoTimer(500);
    worldState = _worldState; 
    robotAction = _robotAction;
    speed = _speed;
}

void InchForward::inch() {
    if (!moving->getReady()) {
        moveInEnemyDirection();
    }
    else if (!stopped->getReady()) {
        robotAction->brake();
    }
    else {
        moving->resetTimer();
        stopped->resetTimer();
    }
}

void InchForward::moveInEnemyDirection() {
    Position enemyPosition = worldState->getLastEnemyPosition();
    if (enemyPosition == Position::Middle_Close || enemyPosition == Position::Middle_Far) {
        robotAction->forward(speed);
    }
    else if (enemyPosition == Position::Left) {
        robotAction->turn(speed - 30, speed);
    }
    else if (enemyPosition == Position::Right) {
        robotAction->turn(speed, speed - 30);
    } else {
        robotAction->forward(speed);
    }
}