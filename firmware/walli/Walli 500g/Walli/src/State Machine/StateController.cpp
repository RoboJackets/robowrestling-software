#include "StateS.cpp"

class StateController {
    StateS current;
    public: 
        StateController() {
            current = *new StateS();
        }
        void transition() {
            if (current.getCondition()) {
                current.setCondition(false);
                current = *current.getNext();
            }
        }
        void setCurrent(StateS c) {
            current = c;
        }

        State getCurrent() {return current.getState();}
};

