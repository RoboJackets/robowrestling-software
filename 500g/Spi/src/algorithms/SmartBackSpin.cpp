#include "algorithms/SmartBackSpin.hpp"

SmartBackSpin::SmartBackSpin(WorldState *_worldState, RobotAction* _robotAction) : Action(-1, 0, _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    lastAction = nullptr;
    backSpinLeft = new BackSpinLeft(robotAction);
    backSpinRight = new BackSpinRight(robotAction);
}

void SmartBackSpin::performAction() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Left || position == Position::On_Line_Both ) {
        backSpinRight->resetAction();
        backSpinRight->run();
        lastAction = backSpinRight;
    }
    if (position == Position::On_Line_Right) {
        backSpinLeft->resetAction();
        backSpinLeft->run();
        lastAction = backSpinLeft;
    }
    if (position == Position::Off_Line) {
        if (lastAction == nullptr) {
            return;
        }
        lastAction->run();
    }
}

void SmartBackSpin::resetTimers() {
    return;
}
