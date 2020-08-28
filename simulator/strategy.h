#ifndef strategy_h
#define strategy_h
#include <vector> 

// stub class for strategy
// every new strategy we create must include strategy_h so since we call upon standardized methods 
// in sim to execute these strategies.
class Strategy {
    public: 
        // returns vector of size 2 containing ints [0, 100] to indicate left and right motor output % respectively 
        virtual std::vector<int> next_action() = 0;
};

#endif