#include "Strategies.h"
#include "worldState.h"
#include "robotAction.h"
#include "Timer.h"
#include "stateEnums.h"
#include <Arduino.h>


Strategies::Strategies(worldState *state, robotAction *robot, Timer *timer) {
    this->state = state;
    this->robot = robot;
    this->timer = timer;
    currentState = IDLE;
}
Strategies::Strategies(worldState *state, robotAction *robot) {
    this->state = state;
    this->robot = robot;
    currentState = IDLE;
}
void Strategies::test() {
    
}

void Strategies::moveForward() {
    robot->moveForward(255);
}

void Strategies::generalStrategy() {
    if (state->getPosition == Position::ON_LINE_FRONT) {
        robot->moveBackward(255);
    } else if (state->getPosition == Position::ON_LINE_BACK) {
        robot->moveForward(255);
    } else if (state->getEnemyPosition() == Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition()== Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition() == Position::FRONT_RIGHT|| state->getEnemyPosition() == Position::BACK_LEFT) {
        robot->turnRight(255);
    } else if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
        robot->moveForward(50);
    } else if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
        robot->moveBackward(50);
    } else if {state->getEnemyPosition() == Position::NONE} {
        robot->turnRight(255);
    }
}

void Strategies::runAway() {
    if (state->getPosition == Position::ON_LINE_FRONT) {
        robot->moveFowardFor(255, 1000);
    } else if (state->getPosition == Position::ON_LINE_BACK) {
        robot->moveBackwardFor(255, 1000);
    } else if (state->getEnemyPosition() == Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition()== Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition() == Position::FRONT_RIGHT|| state->getEnemyPosition() == Position::BACK_LEFT) {
        robot->turnRight(255);
    } else if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
        robot->moveBackward(50);
    } else if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
        robot->moveForward(50);
    } else if {state->getEnemyPosition() == Position::NONE} {
        robot->turnRight(255);
    }
}