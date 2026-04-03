#include "Robot/Algorithms.hpp"

Algorithms :: Algorithms(RobotActions *actions) {
    this->action = actions;
    onStart = true;
}

// MAIN ALGORITHM FUNCTION
void Algorithms :: selectAlgo(EnemyPos enemyPos, OnLine onLine) {
    // Add any one-time on start actions here
    // Current: High priority charge forward for 300 ms (adjust time and speed)
    if (onStart) {
        action -> forward(200, 300, 3);
        onStart = false;
    }

    // Main behavior
    // If enemy is detected, attack
    // If no enemy is detected and on line, move away from line
    // If no enemy is detected and not on line, search for enemy
    if (enemyPos != NONE) {
        slam(enemyPos, onLine);
    } else if (onLine != NONELINE) {
        lineMovement(enemyPos, onLine);
    } else {
        slam(enemyPos, onLine);
    }
}

void Algorithms :: slam(EnemyPos enemyPos, OnLine onLine) {
    // Turn towards enemy and move forward
    if (enemyPos == LEFT) {
        action->turnLeft(100, 0, 2);
    } else if (enemyPos == RIGHT) {
        action->turnRight(100, 0, 2);
    } else if (enemyPos == FRONT) {
        action->forward(100, 0, 2);
    } else {
        action->turnLeft(100, 0, 1);
    }
}

void Algorithms :: lineMovement(EnemyPos enemyPos, OnLine onLine) {
    // Turn away from line and move forward 
    if (onLine == FRONTLINE) {
        action->turnLeft(200, 0, 1);
    } else if (onLine == BACKLINE) {
        action->forward(200, 200, 2);
    } else if (onLine == LEFTLINE) {
        action->turnRight(200, 0, 1);
    } else if (onLine == RIGHTLINE) {
        action->turnLeft(200, 0, 1);
    }
}