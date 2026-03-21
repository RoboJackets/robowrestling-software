#include "Robot/RobotActions.hpp"
#include <Arduino.h>

RobotActions :: RobotActions(int *left, int *right) {
    driver[0] = left;
    driver[1] = right;
    // End time is in milliseconds, pass in time in ms
    endTime = 0;
    // Priority 1: Search, line turning
    // Priority 2: Attacking, moving off line
    // Priority 3: Starting action, other tba
    // Priority in same category is overridden by most recent action
    priority = 0;
}

int RobotActions :: getLeft() {
    return *driver[0];
}

int RobotActions :: getRight() {
    return *driver[1];
}

void RobotActions :: setLeft(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[0] = spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

void RobotActions :: setRight(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[1] = spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

void RobotActions :: forward(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[0] = spd;
        *driver[1] = spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

void RobotActions :: backward(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[0] = -spd;
        *driver[1] = -spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

void RobotActions :: turnLeft(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[0] = -spd;
        *driver[1] = spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

void RobotActions :: turnRight(int spd, int time, int priority) {
    if (priority >= this->priority || (millis() >= endTime)) {
        *driver[0] = spd;
        *driver[1] = -spd;
        this->priority = priority;
        endTime = millis() + time;
    }
}

// For manually checking action completion
bool RobotActions :: actionOver() {
    return millis() >= endTime;
}