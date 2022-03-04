#ifndef opening_h
#define opening_h
#include <vector> 
#include <sensor_struct.h>

// stub class for opening
// every new opening we create must include opening_h so since we call upon standardized methods 
// in sim to execute these strategies.
class Opening {
    public: 
        // returns vector with left and right motor output percentages.
        virtual std::vector<int> execute(SensorData input) = 0;
};

#endif