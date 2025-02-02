#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_


class RobotState {
    private:    
        MoveForward* moveForward;           // pointer to MoveForward instance
        WorldState* worldState;             // pointer to WorldState instance
    public: 
        RobotState();
        virtual void runAlgorithm();
};

#endif