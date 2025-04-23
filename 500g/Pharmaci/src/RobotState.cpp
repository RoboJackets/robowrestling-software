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

void RobotState::calculateState() {
    Position selfPosition = worldState->getSelfPosition();
    Position enemyPosition = worldState->getEnemyPosition();

    // OLD STUFF
    // if (selfPosition != Position::Off_Line) {
    //     if (selfPosition == Position::On_Line) {
    //         robotActions->drive(80, 80);
    //     } else if (selfPosition == Position::On_Line_Left) {
    //         robotActions->drive(80, 0);
    //     } else if (selfPosition == Position::On_Line_Right) {
    //         robotActions->drive(0, 80);
    //     } else {
    //         robotActions->drive(0, 0);

    //     }
    // } else {
    //     if (enemyPosition == Position::Middle_Close) {
    //         robotActions->drive(255, 255);
    //     } else if (enemyPosition == Position::Middle_Far) {
    //         robotActions->drive(80, 80);
    //     } else if (enemyPosition == Position::Left) {
    //         robotActions->drive(0, 80);
    //     } else if (enemyPosition == Position::Right) {
    //         robotActions->drive(80, 0);
    //     } else if (enemyPosition == Position::Left_Middle) {
    //         robotActions->drive(0, 40);
    //     } else if (enemyPosition == Position::Right_Middle) {
    //         robotActions->drive(40, 0);
    //     } else {
    //         robotActions->drive(80, -80);
    //     }
    // }


    // New algorithm (for now)

    // if (selfPosition == Position::On_Line_Left) {
    //     robotActions->drive(0, 100);
    // } else if (selfPosition == Position::On_Line_Right) {
    //            robotActions->drive(100, 0);
 
    // }


    if (enemyPosition == Position::Middle_Close) {
        robotActions->drive(255, 255);
    } else if (enemyPosition == Position::Middle_Far) {
        robotActions->drive(100, 100);
    } else if (enemyPosition == Position::Left) {
        robotActions->drive(-100, 100);
    } else if (enemyPosition == Position::Right) {
        robotActions->drive(100, -100);
    } else if (enemyPosition == Position::None) {
        robotActions->drive(100, -100);
    }
}



