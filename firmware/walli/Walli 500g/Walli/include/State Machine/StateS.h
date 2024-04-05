#ifndef STATE
#define STATE
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
        StateS(State name);

        State getState();
        void setNext(StateS* nextState);

        void setCondition(bool c);

        bool getCondition();

        StateS* getNext();
};
#endif
