#ifndef ALGORITHM_HPP
#include "Robot/robotActions.hpp"

#define ALGORITHM_HPP 

class Algorithm {
    private: 
        RobotActions *action;
    public:
        Algorithm(RobotActions *action);
        void RunItDown();        
};

#endif