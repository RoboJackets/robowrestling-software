#include <State Machine\StateController.h>

/* This class define acts as the "State Machine"
* that will be used within the main method to determine
* which strategy is run when
*
* The flow is OFF -> START -> ATTACK <-> ESCAPE -> OFF
*/

//constructor
StateController::StateController() {
    current = new StateS(State::OFF);
}
//switch between the current state and the next one
void StateController::transition() {
    if (current->getCondition()) {
        current->setCondition(false);
        current = current->getNext();
    }
}
//manually switch to the next state
void StateController::setCurrent(StateS* c) {
    current = c;
}

//reteive the curent state
State StateController::getCurrent() {return current->getState();}


