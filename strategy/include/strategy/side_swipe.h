

#ifndef SIDESWIPE_H
#define SIDESWIPE_H
#include <strategy/strategy.h>


class SideSwipe {
    public: 
        SideSwipe(); 
        std::vector<int> next_action(SensorData input);
        enum State {
            IDLE, 
            CHARGE, 
            ADJUST,
            SEARCH, 
            PUSH_RIGHT,
            PUSH_LEFT
        };
        State updateState(SensorData input);  
    private: 
        State mState;
        
};

#endif