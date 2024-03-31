#include <State Machine\StateS.h>

StateS::StateS(State name) {
    _state = name;
    condition = false;
}

State StateS::getState() {return _state;}
void StateS::setNext(StateS* nextState) { _next = nextState; }
void StateS::setCondition(bool c) {condition = c;}
bool StateS::getCondition() { return condition; }
StateS* StateS::getNext() {return _next;}


