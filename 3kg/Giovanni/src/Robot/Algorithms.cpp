#include "Robot/Algorithms.hpp"

Algorithms :: Algorithms(RobotActions *actions) {
    this->action = actions;
}

// Add more algorithms below
int Algorithms :: slam(EnemyPos enemyPos, OnLine onLine) {
    //checking when we're on the line first
    //Want to figure out which sensors to prioritize
    //If all 4 are on the line, 
    if (onLine != NONELINE) {
       int is_online = lineMovement(enemyPos, onLine);
         if (is_online) {
              return 1;
         }
    }
    if (enemyPos == LEFT) {
        action->turnLeft(200);
        return 1;
    } else if (enemyPos == RIGHT) {
        action->turnRight(200);
        return 1;
    } else if (enemyPos == FRONT) {
        action->forward(200);
        return 1;
    } else {
        action->turnLeft(200);
        return 1;
    }

}

int Algorithms :: lineMovement(EnemyPos enemyPos, OnLine onLine) {
    if (onLine == FRONTLINE) {
        action->turnLeft(200);
        return 1;
    } else if (onLine == BACKLINE) {
        action->forward(200);
        return 1;
    } else if (onLine == LEFTLINE) {
        action->turnRight(200);
        return 1;
    } else if (onLine == RIGHTLINE) {
        action->turnLeft(200);
        return 1;
    }
    return 0;
}