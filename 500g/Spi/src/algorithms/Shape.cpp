#include "algorithms/Shape.hpp"

Shape::Shape(WorldState *_worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    backSpinLeft = new BackSpinLeft(robotAction);
    backSpinRight = new BackSpinRight(robotAction);
}

void Shape::Run() {
    Position position = worldState->getPosition();
    if (position == Position::On_Line_Both) {}
}

