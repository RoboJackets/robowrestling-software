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
    if (state->getEnemyPosition()== Position::FRONT_LEFT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition() == Position::FRONT_RIGHT) {
        robot->turnRight(255);
    }
}

