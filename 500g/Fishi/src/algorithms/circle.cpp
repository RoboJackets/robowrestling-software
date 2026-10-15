#include "algorithms/circle.hpp"

template <typename T>
T clamp(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

Circle::Circle(WorldState *_worldState, RobotAction *_robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    hasDoneStartSequence = false;
    turn90 = new AutoTimer(150);
    robotAction->setSpeed(255);
    whiteAdjust = new AutoTimer(1);
    blackAdjust = new AutoTimer(100);

    rightSpeed = 100;
    leftSpeed = 110;
}

void Circle::run() {
    Position position = worldState->getPosition();
        if (whiteAdjust->getReady() && position == Position::On_Line_Left) {
            if (wasBlack) {
                rightSpeed = 100;
                leftSpeed = 255;
                wasBlack = false;
                wasWhite = true;
            }
            // leftSpeed = clamp<int>(leftSpeed + 1, 0, 255);
            // rightSpeed = clamp<int>(rightSpeed - 1, 0, 255);
            whiteAdjust->resetTimer();
        }
        if (blackAdjust->getReady() && position == Position::Off_Line) {
            if (wasWhite) {
                rightSpeed = 255;
                leftSpeed = 200;
                wasBlack = true;
                wasWhite = false;
            }
            // leftSpeed = clamp<int>(leftSpeed - 1, 0, 255);
            // rightSpeed = clamp<int>(rightSpeed + 1, 0, 255);
            blackAdjust->resetTimer();
        }
        robotAction->turn(leftSpeed, rightSpeed);
    }