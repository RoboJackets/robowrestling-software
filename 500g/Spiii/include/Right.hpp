#ifndef RIGHT_H
#define RIGHT_H

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

/*turn left -> slow turn right till straight -> brazil*/
class Right {
    private:
        const int MAX_SPEED = 255;
        const int MOD = 150;
        const int LEFT_TURN_TIMER_DURATION = 90;
        const int RIGHT_TURN_TIMER_DURATION = 320 + LEFT_TURN_TIMER_DURATION;
        const int FINAL_SPIN_TIMER_DURATION = 70 + RIGHT_TURN_TIMER_DURATION;
        bool start_flag;
        Timer *left_turn_timer;
        Timer *right_turn_timer;
        Timer *final_spin_timer;
        WorldState *worldState;
        RobotAction *robotAction;
    public:
        Right(WorldState* _worldState, RobotAction* _robotAction);
        bool run();
};

#endif