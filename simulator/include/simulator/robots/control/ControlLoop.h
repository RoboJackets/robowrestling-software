#pragma once 

#include <chrono> 

class ControlLoop {
    private: 
        double _setpoint; 

    public: 
        virtual ~ControlLoop(); 
        ControlLoop(double setpoint): _setpoint(setpoint){}
        
        virtual void SetTarget(double setpoint) {
            _setpoint = setpoint; 
        }

        virtual double Update(double current) = 0;

};