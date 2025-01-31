#include "Robot/robotActions.hpp"
#ifndef ALGORITHM_HPP

#define ALGORITHM_HPP 

class Algorithm {
    private: 
        RobotActions *action;
    public:
        Algorithm(RobotActions *action);
        void RunItDown();
};

#endif