#ifndef DASHLEFT_H
#define DASHLEFT_H

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

/*turn left -> slow turn right till straight -> brazil*/
class DashLeft {
    private:
        const int MAX_SPEED = 255;
        const int MOD = 150;
        const int LEFT_TURN_TIMER_DURATION = 80;
        const int RIGHT_TURN_TIMER_DURATION = 150 + LEFT_TURN_TIMER_DURATION;
        const int FINAL_SPIN_TIMER_DURATION = 70 + RIGHT_TURN_TIMER_DURATION;
        bool start_flag;
        Timer *left_turn_timer;
        Timer *right_turn_timer;
        Timer *final_spin_timer;
        WorldState *worldState;
        RobotAction *robotAction;
    public:
        DashLeft(WorldState* _worldState, RobotAction* _robotAction);
        bool run();
};

#endif