
//switch to enums!

enum State {
    OFF,
    START,
    ATTACK,
    ESCAPE
};
class StateS {
    private: 
        State _state;
        StateS* _next;
        bool condition;

    public: 
        StateS() {
            _state = OFF;
            condition = false;
        }
        StateS(State name) {
            _state = name;
            condition = false;
        }

        void setNext(StateS* nextState) { _next = nextState; }

        void setCondition(bool c) {condition = c;}
        State getState() {return _state;}

        bool getCondition() { return condition; }

        StateS* getNext() {return _next;}
};

