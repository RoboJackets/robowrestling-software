#ifndef STATE
#define STATE

/* This class defines what each state
* consists of, including what the 
* state that follows is, and whether or not
* the current state is done executing or not
*/
enum State {
    OFF, //beginning of match, sample the floor
    ATTACK, //spin-and-attack
    ESCAPE //back up away from the line
};
class StateS {
    private: 
        State _state; //the current state
        StateS* _next; //the state that follows
        bool condition; //whether or not we finished this state or not

    public: 
        //constructor
        StateS(State name);

        //get the current state
        State getState();
        //get the next state
        void setNext(StateS* nextState);

        //manually set whether or not this state is done running or not
        void setCondition(bool c);

        //manually retrieve whether or not this state is done running or not
        bool getCondition();

        //get the next state
        StateS* getNext();
};
#endif
