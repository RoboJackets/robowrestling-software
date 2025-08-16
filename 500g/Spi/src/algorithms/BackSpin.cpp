#include "algorithms/BackSpin.hpp"

/**
 * 400 ms backing up (after getting off white)
 * 250 ms spinning
 */
BackSpin::BackSpin(WorldState *_worldState, RobotAction *_robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    backup = new AutoTimer(250);
    spin = new AutoTimer(250 + 400);
}

void BackSpin::run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Left || position == Position::On_Line_Right) {
        backup->resetTimer();
        spin->resetTimer();
    }
    if (position == Position::On_Line_Both) robotAction->back(255);
    else if (position == Position::On_Line_Left) robotAction->turnBack(255, 255 - 70);
    else if (position == Position::On_Line_Right) robotAction->turnBack(255 - 70, 255);
    if (position == Position::Off_Line) {
        if (!backup->getReady()) robotAction->back(255);
        else if (!spin->getReady()) {
            Position lastPosition = worldState->getLastPosition();
            if (lastPosition == Position::On_Line_Left) robotAction->spinLeft();
            if (lastPosition == Position::On_Line_Right) robotAction->spinRight();
        }
    }
    if (position == Position::Off_Line && backup->getReady() && spin->getReady()) robotAction->brake();
}