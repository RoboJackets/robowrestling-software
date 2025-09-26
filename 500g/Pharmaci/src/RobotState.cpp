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

// RobotState ctor (fix intervals)
RobotState::RobotState(WorldState* worldStatePtr, RobotActions* robotActionsPtr,
                       MotorDriver* leftMotorDriverPointer, MotorDriver* rightMotorDriverPointer) {
    worldState = worldStatePtr;
    robotActions = robotActionsPtr;
    leftMotorDriver = leftMotorDriverPointer;
    rightMotorDriver = rightMotorDriverPointer;

    turnTimer  = new Timer();  turnTimer->setTimeInterval(300);  // rotate phase
    backupTimer = new Timer(); backupTimer->setTimeInterval(300); // back-up phase


    isTurning = false;
    phase = Phase::Idle;
    turnDir = TurnDir::None;
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



// This algorithm is a turret essentially, it always tries to look towards the robot
// It continues turning based on its last state if it doesn't detect anything

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
    const int CRUISE_SPEED   = 75;
    const int BACKUP_SPEED   = 200;
    const int ROTATE_SPEED   = 200;

    const int BACKUP_MS_SIDE = 100;
    const int BACKUP_MS_BOTH = 200;
    const int ROTATE_MS_SIDE = 120;
    const int ROTATE_MS_BOTH = 180;

    // debounce window to decide "both" vs "side-only"
    const int BOTH_WINDOW_MS = 20;

    // --- NEW: latch tunables (turn-hold after Left/Right detection)
    const int LATCH_MS = 100;             // hold hard turn for ~0.6s
    const int MIDDLE_CONFIRM_MS = 150;    // see middle for this long to break latch early

    // Debounce state (static locals: no header changes)
    static bool     pendingLine = false;       // we saw a side hit and are waiting
    static TurnDir  pendingDir  = TurnDir::None;
    static int      pendingT0   = 0;

    // --- NEW: latch state (locals only)
    static bool     latchActive = false;
    static TurnDir  latchDir    = TurnDir::None;
    static int      latchT0     = 0;
    static int      middleSeenT0 = -1;

    Position selfPos = worldState->getSelfPosition();
    Position enemyPos = worldState->getEnemyPosition();  // sector detection

    // keep timers current
    turnTimer->setCurrentTime(time);
    backupTimer->setCurrentTime(time);

    // === Maneuver in progress ===
    if (isTurning) {
        // if we are in a line-save maneuver, cancel any aim latch
        latchActive = false;

        if (phase == Phase::BackingUp) {
            if (!backupTimer->getReady()) {
                robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                return;
            }
            phase = Phase::Rotating;
            turnTimer->setPreviousTime(time);
        }

        if (phase == Phase::Rotating) {
            if (!turnTimer->getReady()) {
                if (turnDir == TurnDir::Left)  robotActions->drive(-ROTATE_SPEED, ROTATE_SPEED);
                else                            robotActions->drive( ROTATE_SPEED, -ROTATE_SPEED);
                return;
            }
            // finish
            isTurning = false;
            phase = Phase::Idle;
            turnDir = TurnDir::None;
        }
    }

    // === Debounce window handling (only when not turning) ===
    if (!isTurning && pendingLine) {
        // if both sensors detected during window -> commit as BOTH
        if (selfPos == Position::On_Line) {
            // choose durations (BOTH) and direction default
            backupTimer->setTimeInterval(BACKUP_MS_BOTH);
            turnTimer->setTimeInterval(ROTATE_MS_BOTH);
            turnDir = TurnDir::Right; // consistent default for "both"
            // start maneuver
            isTurning = true;
            phase = Phase::BackingUp;
            backupTimer->setPreviousTime(time);
            pendingLine = false;
            latchActive = false; // edge safety cancels aim latch
            robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
            return;
        }
        // if window expired -> commit as SIDE
        if (time - pendingT0 >= BOTH_WINDOW_MS) {
            backupTimer->setTimeInterval(BACKUP_MS_SIDE);
            turnTimer->setTimeInterval(ROTATE_MS_SIDE);
            turnDir = pendingDir; // the side we latched
            isTurning = true;
            phase = Phase::BackingUp;
            backupTimer->setPreviousTime(time);
            pendingLine = false;
            latchActive = false; // edge safety cancels aim latch
            robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
            return;
        }
        // still waiting inside window
        robotActions->drive(0, 0);
        return;
    }

    // === New detection (no maneuver active and no pending) ===
    if (!isTurning && !pendingLine) {
        if (selfPos == Position::On_Line) {
            // both at once -> commit immediately to BOTH
            backupTimer->setTimeInterval(BACKUP_MS_BOTH);
            turnTimer->setTimeInterval(ROTATE_MS_BOTH);
            turnDir = TurnDir::Right; // default on both
            isTurning = true;
            phase = Phase::BackingUp;
            backupTimer->setPreviousTime(time);
            pendingLine = false;
            latchActive = false; // edge safety cancels aim latch
            robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
            return;
        }
        if (selfPos == Position::On_Line_Left) {
            // start debounce window for possible BOTH
            pendingLine = true;
            pendingDir  = TurnDir::Right; // turn away from left
            pendingT0   = time;
            robotActions->drive(0, 0);    // kill momentum while waiting
            return;
        }
        if (selfPos == Position::On_Line_Right) {
            pendingLine = true;
            pendingDir  = TurnDir::Left;  // turn away from right
            pendingT0   = time;
            robotActions->drive(0, 0);
            return;
        }
    }

    // ====== ENEMY DETECTION (your exact speeds) ======
    double speed        = 75.0;
    double rotSpeed     = 255.0;
    double slowRotSpeed = 100.0;

    // --- NEW: create/maintain latch when we see Left/Right near the boundary
    if (!latchActive && (enemyPos == Position::Left || enemyPos == Position::Right)) {
        latchActive = true;
        latchDir    = (enemyPos == Position::Left) ? TurnDir::Left : TurnDir::Right;
        latchT0     = time;
        middleSeenT0 = -1;
    }

    // --- NEW: latched behavior (turn hard for a short dwell; break early if centered)
    if (latchActive) {
        // if any middle sector is seen, start/confirm early exit
        bool middleNow =
            (enemyPos == Position::Left_Middle) || (enemyPos == Position::Left_Middle_Close) ||
            (enemyPos == Position::Right_Middle) || (enemyPos == Position::Right_Middle_Close) ||
            (enemyPos == Position::Middle_Far)   || (enemyPos == Position::Middle_Close);

        if (middleNow) {
            if (middleSeenT0 < 0) middleSeenT0 = time;
            if (time - middleSeenT0 >= MIDDLE_CONFIRM_MS) {
                latchActive = false; // hand back to normal logic
            }
        } else {
            middleSeenT0 = -1; // reset confirmation timer
        }

        // timeout to avoid over-committing if we never see middle
        if (time - latchT0 >= LATCH_MS) {
            latchActive = false;
        }

        // while still latched, keep turning hard toward the side and return
        if (latchActive) {
            if (latchDir == TurnDir::Left)  robotActions->drive(-rotSpeed,  rotSpeed);
            else                             robotActions->drive( rotSpeed, -rotSpeed);
            return;
        }
        // if latch just ended, fall through to your normal enemy logic below
    }

    // === Your original enemy reaction logic ===
    if (enemyPos == Position::Middle_Close || enemyPos == Position::Middle_Far) {
        // stop when enemy dead ahead (you can change to charge if desired)
        robotActions->drive(200.0, 200.0);

    } else if (enemyPos == Position::Right_Middle_Close) {
        robotActions->drive(200.0, 200.0);

    } else if (enemyPos == Position::Left_Middle_Close) {
        robotActions->drive(200.0, 200.0);

    } else if (enemyPos == Position::Right_Middle) {
        robotActions->drive(255.0, 200.0);

    } else if (enemyPos == Position::Left_Middle) {
        robotActions->drive(200.0, 255.0);

    } else if (enemyPos == Position::Right) {
        robotActions->drive(255.0, -255.0);

    } else if (enemyPos == Position::Left) {
        robotActions->drive(-255.0, 255.0);

    } else if (enemyPos == Position::None) {
        // idle mode → drive forward
        robotActions->drive(75.0, 75.0);
    }

    // === Default: cruise ===
}



// Zig-zag search



// Full Algorithm

