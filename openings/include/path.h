#ifndef path_h
#define path_h
#include <vector> 

// stub class for path
// every new path we create must include path_h so since we call upon standardized methods 
// in sim to execute these strategies.
class Path {
    private:
        std::vector<int> start_point;
        std::vector<int> end_point; // where should the robot end up.
    public:
        Path();
        Path(std::vector<int> sp);
        virtual std::vector<int> next_action(); // determine next motor control to get to end point.
    
};

#endif