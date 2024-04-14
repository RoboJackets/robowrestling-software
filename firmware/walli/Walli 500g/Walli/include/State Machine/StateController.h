#ifndef SC
#define SC
#include <State Machine\StateS.h>

class StateController {
    StateS* current;
    public: 
        //constructor
        StateController();
        //switch between the current state and the next one
        void transition();
        //manually switch to the next state
        void setCurrent(StateS* c);
        //reteive the curent state
        State getCurrent();
};
#endif

