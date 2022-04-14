

#ifndef SIDESWIPE_H
#define SIDESWIPE_H
#include <strategy/strategy.h>
#include <iostream>
#include <chrono>
#include <math.h>
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


#define KP (0.63694267515)

class SideSwipe {
    public: 
        SideSwipe(); 
        std::vector<int> next_action(SensorData input);
        enum State {
            IDLE, 
            CHARGE, 
            APPROACH,
            SEARCH_LEFT,
            SEARCH_RIGHT, 
            CURVE, 
            BOUNDRY, 
        };
        State updateState(SensorData input);  
    private: 
        State mState;
        bool targetLock;
        double currentAngle;  
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
        
        
};

#endif