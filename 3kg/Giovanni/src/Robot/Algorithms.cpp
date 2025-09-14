#include "Robot/Algorithms.hpp"
#include "Enumerations/EnemyPos.cpp"
#include "Enumerations/OnLine.cpp"

Algorithms :: Algorithms(RobotActions *actions) {
    this->action = action;
}

// Add more algorithms below
void Algorithms :: slam(EnemyPos enemyPos, OnLine onLine) {
    //checking when we're on the line first
    //Want to figure out which sensors to prioritize
    //If all 4 are on the line, 
    if (enemyPos == LEFT) {
        action->turnLeft(200);
    } else if (enemyPos == RIGHT) {
        action->turnRight(200);
    } else if (enemyPos == FRONT) {
        action->forward(200);
    } else {
        action->turnLeft(200);

    }

}