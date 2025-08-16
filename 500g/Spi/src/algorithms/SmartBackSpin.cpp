#include "algorithms/SmartBackSpin.hpp"

SmartBackSpin::SmartBackSpin(WorldState *_worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    backSpinLeft = new BackSpinLeft(robotAction);
    backSpinRight = new BackSpinRight(robotAction);
}

void SmartBackSpin::run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Both) { robotAction->back(255); }
    if (position == Position::On_Line_Left) {
        backSpinRight->resetAction();
        backSpinRight->run();
        lastAction = backSpinRight;
    }
    if (position == Position::On_Line_Right) {
        backSpinLeft->resetAction();
        backSpinLeft->run();
        lastAction = backSpinLeft;
    }
    if (position == Position::Off_Line && lastAction->getActionCompleted()) {
        robotAction->forward(80);
    }
}
