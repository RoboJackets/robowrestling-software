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
void Strategies::test() {
    timer->setTimeInterval(1000);
    timer->setCurrentTime(millis());
    timer->setPreviousTime(millis());
    robot->moveForward(255);
    while (timer->getReady()) {
        timer->setCurrentTime(millis());
    }
    robot->stop();
}

void Strategies::moveForward() {
    robot->moveForward(255);
}

void Strategies::generalStrategy() {
    
}

