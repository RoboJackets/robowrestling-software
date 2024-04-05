#include <State Machine\StateController.h>

//see include\State Machine \StateController.h

StateController::StateController() {
    current = new StateS(State::OFF);
}
void StateController::transition() {
    if (current->getCondition()) {
        current->setCondition(false);
        current = current->getNext();
    }
}
void StateController::setCurrent(StateS* c) {
    current = c;
}

State StateController::getCurrent() {return current->getState();}


