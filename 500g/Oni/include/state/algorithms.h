#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "../../Oni/include/motor/motor_driver.h"
#include "world_state.h"
#include "robot_state.h"
#include "../enums/state_enums.h"
#include "actions/robot_action.h"

class algorithms {
    private:
        RobotAction* roboAction;
        world_state* worldState;

    public:
        algorithms(RobotAction* robo_actions, world_state* world);

        void go_forward();
};
#endif