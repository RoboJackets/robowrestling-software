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

RobotState::RobotState(WorldState *worldStatePtr, RobotActions *robotActionsPtr, MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer) {
    worldState = worldStatePtr;
    robotActions = robotActionsPtr;
    leftMotorDriver = leftMotorDriverPointer;
    rightMotorDriver = rightMotorDriverPointer;
    turnTimer = new Timer();
    turnTimer -> setTimeInterval(1000); // 1 second interval
    backupTimer =  new Timer();
    backupTimer -> setTimeInterval(1000); // 0.3 second interval
    backingUp = false;

}

// void RobotState::calculateState() {
//     Position selfPosition = worldState->getSelfPosition();
//     Position enemyPosition = worldState->getEnemyPosition();
//     double speed = 150.0;
//     double rotSpeed = 150.0;

//     if (enemyPosition == Position::Middle_Close) {
//         robotActions->drive(speed, speed);
//     } else if (enemyPosition == Position::Middle_Far) {
//         robotActions->drive(speed, speed);
//     } else if (enemyPosition == Position::Left) {
//         robotActions->drive(-rotSpeed, rotSpeed);
//     } else if (enemyPosition == Position::Right) {
//         robotActions->drive(rotSpeed, -rotSpeed);
//     } else if (enemyPosition == Position::None) {
//         if (selfPosition == Position::On_Line) {
//             robotActions->drive(-speed, -speed);
//         } else if (selfPosition == Position::On_Line_Left) {
//             robotActions->drive(-rotSpeed, 0);
//         } else if (selfPosition == Position::On_Line_Right) {
//             robotActions->drive(0, -rotSpeed);
//         } else {
//             if (worldState->getLastEnemyPosition() == Position::Left) {
//                 robotActions->drive(-rotSpeed, rotSpeed);
//             } else if (worldState->getLastEnemyPosition() == Position::Right) {
//                 robotActions->drive(rotSpeed, -rotSpeed);
//             } else {
//                 robotActions->drive(rotSpeed, -rotSpeed);
//             }
//         }
//     }
// }



//Turret State

// void RobotState::calculateState() {
//     Position selfPosition = worldState->getSelfPosition();
//     Position enemyPosition = worldState->getEnemyPosition();
//     double speed = 100.0;
//     double rotSpeed = 150.0;
//     double slowRotSpeed = 100.0;

//     if (enemyPosition == Position::Middle_Close || enemyPosition == Position::Middle_Far) {
//         robotActions->drive(0.0, 0.0);

//     } else if (enemyPosition == Position::Right_Middle_Close) {
//         robotActions->drive(slowRotSpeed, -slowRotSpeed);
//     } else if (enemyPosition == Position::Left_Middle_Close) {
//         robotActions->drive(-slowRotSpeed, slowRotSpeed);
//     } else if (enemyPosition == Position::Right_Middle) {
//         robotActions->drive(slowRotSpeed, -slowRotSpeed);
//     } else if (enemyPosition == Position::Left_Middle) {
//         robotActions->drive(-slowRotSpeed, slowRotSpeed);
//     } else if (enemyPosition == Position::Right) {
//         robotActions->drive(rotSpeed, -rotSpeed);
//     } else if (enemyPosition == Position::Left) {
//         robotActions->drive(-rotSpeed, rotSpeed);
//     } else if (enemyPosition == Position::None) {
//     }
// }

// Timer based state

void RobotState::calculateState(int time) {
    Position selfPosition = worldState->getSelfPosition();
    double speed = 150.0;
    double rotSpeed = 150.0;
    bool turning = false;

    if (selfPosition == Position::On_Line || selfPosition == Position::On_Line_Left || selfPosition == Position::On_Line_Right) {
        turnTimer->setPreviousTime(time);

        if (!turnTimer->getReady()) {
            turning = false;
            robotActions->drive(rotSpeed, -rotSpeed);
        } else {
            turning = true;
        }
    } else if (!turning && selfPosition == Position::Off_Line) {
        robotActions->drive(speed, speed);
    }
}