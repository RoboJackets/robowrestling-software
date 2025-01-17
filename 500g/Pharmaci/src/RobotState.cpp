/*
Possible states:

if (frontLineSensor) {
    turn around
}

if (noRobotDetected) {
    move in a small circle (not rotate in place). 
    This way, we are not a sitting duck 
    and can force another robot to recalculate while also looking for them
}

if (robotDetected on left/right) {
    turn until robot is in middle
}

if (robot detected in middle) {
    wait a second
    if (they get closer to us) {
        run broken curve algorithm (turn right a bit drive in a slight circle to get around the team)
    }
    if (they don't get closer to us (assume they're spinning in place)) {
        go towards them full speed
    }
}
*/

#include <RobotState.h>

RobotState::RobotState(WorldState *worldStatePtr, RobotActions *robotActionsPtr) {
    worldState = worldStatePtr;
    robotActions = robotActionsPtr;
}


