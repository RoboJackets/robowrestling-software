#include "Robot/RobotActions.cpp"
#include "Sensors/WorldState.cpp"
#ifndef ROBOTSTATE_HPP

#define ROBOTSTATE_HPP 

class RobotState {
    private: 
        RobotActions RobotActions;
        WorldState worldState;
    public:
        void calculateState();
};

#endif