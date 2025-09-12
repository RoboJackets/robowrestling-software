#include "Robot/RobotActions.hpp"

RobotActions :: RobotActions(int *left, int *right) {
    driver[0] = left;
    driver[1] = right;
}

int RobotActions :: getLeft() {
    return *driver[0];
}

int RobotActions :: getRight() {
    return *driver[1];
}

void RobotActions :: setLeft(int spd) {
    *driver[0] = spd;
}

void RobotActions :: setRight(int spd) {
    *driver[1] = spd;
}

void RobotActions :: forward(int spd) {
    *driver[0] = spd;
    *driver[1] = spd;
}

void RobotActions :: backward(int spd) {
    *driver[0] = -spd;
    *driver[1] = -spd;
}

void RobotActions :: turnLeft(int spd) {
    *driver[0] = -spd;
    *driver[1] = spd;
}

void RobotActions :: turnRight(int spd) {
    *driver[0] = spd;
    *driver[1] = -spd;
}

