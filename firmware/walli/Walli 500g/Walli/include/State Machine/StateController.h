#ifndef SC
#define SC
#include <State Machine\StateS.h>

class StateController {
    StateS* current;
    public: 
        StateController();
        void transition();
        void setCurrent(StateS* c);
        //C:\msys64
        State getCurrent();
};
#endif

