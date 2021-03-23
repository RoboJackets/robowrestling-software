#ifndef strategy_h
#define strategy_h
#include <vector> 
#include <sensor_struct.h>

// stub class for strategy
// every new strategy we create must include strategy_h so since we call upon standardized methods 
// in sim to execute these strategies.
class Strategy {
    public: 
        // returns vector of size 2 containing ints [-100, 100] to indicate left and right motor output % respectively 
        std::vector<int> next_action() { //A next action method should always return a size 2 int vector, but can be overloaded to take an input of sensor structs
            return {0, 0};
        };
};

#endif