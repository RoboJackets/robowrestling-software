#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_

// add robotAction instance and worldState instance
// encapsulation (getters and setters)
// make runAlgorithm return an enumeration of actions

class RobotState {

    public:
        RobotState();
        virtual void runAlgorithm();
};

#endif