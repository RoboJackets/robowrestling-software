#include "Robot/RobotActions.hpp"

RobotActions :: RobotActions(int left, int right) {
    driver[0] = left;
    driver[1] = right;
}

int RobotActions :: getLeft() {
    return driver[0];
}

int RobotActions :: getRight() {
    return driver[1];
}

void RobotActions :: Forward(int left, int right) {
    driver[0] = left;
    driver[1] = right;
}



