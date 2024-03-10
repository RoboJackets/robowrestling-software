#include <string>
class StateS {
    private: 
        std::string state_name;
        StateS* next;
        bool condition;

    public: 
        StateS() {
            state_name = "";
            next = NULL;
            condition = false;
        }
        StateS(std::string name) {
            state_name = name;
            next = NULL;
            condition = false;
        }

        void setNext(StateS *nextState) { next = nextState; }

        void setCondition(bool c) { condition = c; }
        void setName(std::string name) {state_name = name;}

        bool getCondition() { return condition; }

        StateS* getNext() {return next;}
};

