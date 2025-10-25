#include "algorithms/Shape.hpp"

Shape::Shape(WorldState *_worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    previousAction = nullptr;
    backSpinLeft = new BackSpin(robotAction, true);
    backSpinRight = new BackSpin(robotAction, false);
}

void Shape::run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Both || position == Position::On_Line_Right) {
        backSpinRight->resetAction();
        backSpinRight->run();
        previousAction = backSpinRight;
    }
    if (position == Position::On_Line_Left) {
        backSpinLeft->resetAction();
        backSpinLeft->run();
        previousAction = backSpinLeft;
    }
    if (position == Position::Off_Line) {
        if (previousAction == nullptr || previousAction->getActionCompleted()) { robotAction->forward(60); }
        else { previousAction->run(); }
    }
}

