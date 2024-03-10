#include "StateS.cpp"

class StateController {
    StateS current;
    public: 
        StateController() {
        }
        void transition() {
            if (current.getCondition()) {
                current = *current.getNext();
            }
        }
        void setCurrent(StateS &c) {
            current = c;
        }

        StateS getCurrent() {return current;}
};

