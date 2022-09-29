#pragma once 
#include <simulator/robots/control/ControlLoop.h>


class PIDLoop : public ControlLoop {
    private: 
        double KP;
        double KI;  
        double KD;
        std::chrono::time_point<std::chrono::system_clock> _lastTime;
    
    public: 
        double Update(double current); 
        PIDLoop(double setpoint): ControlLoop(setpoint) {
            KP = 0; 
            KI = 0;
            KD = 0;
        }





};


