#include <State Machine\StateS.h>

/* This class defines what each state
* consists of, including what the 
* state that follows is, and whether or not
* the current state is done executing or not
*/

//constructor
StateS::StateS(State name) {
    _state = name;
    condition = false;
}

//get the current state
State StateS::getState() {
    return _state;
}
//get the next state
void StateS::setNext(StateS* nextState) { 
    _next = nextState;
}
//manually set whether or not this state is done running or not
void StateS::setCondition(bool c) {
    condition = c;
}
//manually retrieve whether or not this state is done running or not
bool StateS::getCondition() {
    return condition; 
}
//get the next state
StateS* StateS::getNext() {
    return _next;
}


