#include "Robot/Algorithms.hpp"

Algorithms :: Algorithms(RobotActions *actions) {
    this->action = actions;
    onStart = true;
}

// MAIN ALGORITHM FUNCTION
void Algorithms :: selectAlgo(EnemyPos enemyPos, OnLine onLine) {
    // Add any one-time on start actions here
    // Current: High priority charge forward for 100 ms (adjust time and speed)
    if (onStart) {
        // parameters: (speed, time (in milliseconds), priority)
        action->forward(80, 100, 7);
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
        lineMovement(enemyPos, onLine);
    }
}

void Algorithms :: slam(EnemyPos enemyPos, OnLine onLine) {
    // Turn towards enemy and move forward
    // Otherwise default behavior is to move forward
    if (enemyPos == LEFT) {
        action->turnLeft(80, 0, 6);
        action->setState(0);
    } else if (enemyPos == RIGHT) {
        action->turnRight(80, 0, 6);
        action->setState(0);
    } else if (enemyPos == FRONT) {
        action->forward(80, 0, 6);
        action->setState(0);
    } else {
        // default behavior
        action->forward(50, 0, 1);
    }
}

void Algorithms :: lineMovement(EnemyPos enemyPos, OnLine onLine) {
    // If we just backed up, turn around
    // turn right if backed off both line or left line
    // turn left if backed off right line
    int state = action->getState();
    if (state == 1) {
        action->turnRight(60, 150, 4);
        return;
    } else if (state == 2) {
        action->turnLeft(60, 150, 4);
        return;
    }

    // Move away from line by backing up or going forward
    if (onLine == BLLINE || onLine == BRLINE) {
        action->forward(80, 200, 5);
    } else if (onLine == FLLINE) {
        action->backward(80, 400, 5);
        action->setState(1);
    } else if (onLine == FRLINE) {
        action->backward(80, 400, 5);
        action->setState(2);
    }
}