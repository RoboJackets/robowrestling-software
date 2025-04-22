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
    sweep = true;
    direction = false;

}
Strategies::Strategies(worldState *state, robotAction *robot) {
    this->state = state;
    this->robot = robot;
    currentState = IDLE;
    sweep = true;
    direction = false;
}
void Strategies::test() {
    
}

void Strategies::moveForward() {
}

void Strategies::generalStrategyBAD() {
    if (sweep) {
        if (state->getEnemyPosition() == Position::NONE){
            if (state->getPosition() == Position::ON_LINE_FRONT || state->getPosition() == Position::ON_LINE_BACK) {
                direction = !direction;
                digitalWrite(LED_BUILTIN, HIGH);
                if (direction) {
                    // robot->turnLeftFor(250, 550);
                    robot->moveForwardFor(50, 1000);
                } else {
                    // robot->turnRightFor(250, 150);
                    robot->moveBackwardFor(50, 1000);
                }
                digitalWrite(LED_BUILTIN, HIGH);
            }
            if (direction) {
                robot->moveForward(50);
            } else {
                robot->moveBackward(50);
            }
        } else {
            sweep = false;
        }
    }
    if (!sweep) {
        if (state->getPosition() == Position::ON_LINE_FRONT) {
            if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
                robot->moveForward(255);
            } else {
                robot->moveBackward(255);
            }
        } else if (state->getPosition() == Position::ON_LINE_BACK) {
            if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
                robot->moveBackward(255);
            } else {
                robot->moveForward(255);
            }
        } else if (state->getEnemyPosition() == Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
            robot->turnLeft(140);
        } else if (state->getEnemyPosition()== Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
            robot->turnLeft(140);
        } else if (state->getEnemyPosition() == Position::FRONT_RIGHT|| state->getEnemyPosition() == Position::BACK_LEFT) {
            robot->turnRight(140);
        } else if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
            robot->moveForward(255);
        } else if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
            robot->moveBackward(255);
        } else if (state->getEnemyPosition() == Position::NONE) {
            sweep = true;
            if (state->getLastEnemyPosition() == Position::MIDDLE_FRONT || state->getLastEnemyPosition() == Position::FRONT_LEFT || state->getLastEnemyPosition() == Position::FRONT_RIGHT) {
                direction = false;
            } else {
                direction = true;
            }
        }
    }
}

void Strategies::generalStrategy() {
    if (state->getPosition() == Position::ON_LINE_FRONT) {
        if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
            robot->moveForward(255);
        } else {
            robot->moveBackward(255);
        }
    } else if (state->getPosition() == Position::ON_LINE_BACK) {
        if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
            robot->moveBackward(255);
        } else {
            robot->moveForward(255);
        }
    } else if (state->getEnemyPosition() == Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(200);
    } else if (state->getEnemyPosition() == Position::FRONT_RIGHT|| state->getEnemyPosition() == Position::BACK_LEFT) {
        robot->turnRight(200);
    } else if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
        robot->moveForward(255);
    } else if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
        robot->moveBackward(255);
    } else if (state->getEnemyPosition() == Position::NONE) {
        if (state->getLastEnemyPosition() == Position::MIDDLE_FRONT || state->getLastEnemyPosition() == Position::FRONT_LEFT || state->getLastEnemyPosition() == Position::BACK_RIGHT) {
            robot->turnLeft(50);
        } else {
            robot->turnRight(50);
        }
    }
}

void Strategies::runAway() {
    if (state->getPosition() == Position::ON_LINE_FRONT) {
        robot->moveForwardFor(255, 1000);
    } else if (state->getPosition() == Position::ON_LINE_BACK) {
        robot->moveBackwardFor(255, 1000);
    } else if (state->getEnemyPosition() == Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition()== Position::FRONT_LEFT || state->getEnemyPosition() == Position::BACK_RIGHT) {
        robot->turnLeft(255);
    } else if (state->getEnemyPosition() == Position::FRONT_RIGHT|| state->getEnemyPosition() == Position::BACK_LEFT) {
        robot->turnRight(255);
    } else if (state->getEnemyPosition() == Position::MIDDLE_FRONT) {
        robot->moveBackward(255);
    } else if (state->getEnemyPosition() == Position::MIDDLE_BACK) {
        robot->moveForward(255);
    } else if (state->getEnemyPosition() == Position::NONE) {
        robot->turnRight(255);
    }
}