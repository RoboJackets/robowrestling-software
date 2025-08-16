#ifndef BACKSPIN_H
#define BACKSPIN_H

#include "utility/Action.hpp"
#include "utility/AutoTimer.hpp"
#include "RobotAction.h"
#include "WorldState.h"


class BackSpin : public Action {
    private:
        RobotAction *robotAction;
        AutoTimer *backup;
        AutoTimer *spin;
        bool spinDirection;
    protected:
        void performAction();
    public:
        /// @brief 
        /// @param _worldState 
        /// @param _robotAction 
        /// @param _spinDirection if true spin left, if false spin right
        BackSpin(WorldState *_worldState, RobotAction *_robotAction, bool _spinDirection);
};

#endif