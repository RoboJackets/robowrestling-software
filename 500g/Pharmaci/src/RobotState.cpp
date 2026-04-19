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

    memeTimer = new Timer();

    isTurning = false;
    phase = Phase::Idle;
    turnDir = TurnDir::None;
}


void RobotState::turretState() {
    Position selfPosition = worldState->getSelfPosition();
    Position enemyPosition = worldState->getEnemyPosition();
    double speed = 100.0;
    double rotSpeed = 150.0;
    double slowRotSpeed = 100.0;

    if (enemyPosition == Position::Middle_Close || enemyPosition == Position::Middle_Far) {
        robotActions->drive(0.0, 0.0);

    } else if (enemyPosition == Position::Right_Middle_Close) {
        robotActions->drive(slowRotSpeed, -slowRotSpeed);
    } else if (enemyPosition == Position::Left_Middle_Close) {
        robotActions->drive(-slowRotSpeed, slowRotSpeed);
    } else if (enemyPosition == Position::Right_Middle) {
        robotActions->drive(slowRotSpeed, -slowRotSpeed);
    } else if (enemyPosition == Position::Left_Middle) {
        robotActions->drive(-slowRotSpeed, slowRotSpeed);
    } else if (enemyPosition == Position::Right) {
        robotActions->drive(rotSpeed, -rotSpeed);
    } else if (enemyPosition == Position::Left) {
        robotActions->drive(-rotSpeed, rotSpeed);
    } else if (enemyPosition == Position::None) {
    }
}

void RobotState::calculateState(uint32_t time) {
    const int BACKUP_SPEED   = 200;
    const int ROTATE_SPEED   = 200;

    const int BACKUP_MS_SIDE = 200; 
    const int BACKUP_MS_BOTH = 250;
    const int ROTATE_MS_SIDE = 80;
    const int ROTATE_MS_BOTH = 80;

    const int BOTH_WINDOW_MS = 20;

    const int LATCH_MS = 30;              // hold hard turn briefly
    const int MIDDLE_CONFIRM_MS = 20;     // see middle this long to break latch early

    const int MIN_BACKUP_DWELL_MS = 60;   // must back up at least this long
    const int MIN_ROTATE_DWELL_MS = 80;  // must rotate at least this long

    static bool     pendingLine = false;       // we saw a side hit and are waiting
    static TurnDir  pendingDir  = TurnDir::None;
    static int      pendingT0   = 0;

    // Latch state
    static bool     latchActive  = false;
    static TurnDir  latchDir     = TurnDir::None;
    static int      latchT0      = 0;
    static int      middleSeenT0 = -1;

    static uint32_t backupEarliestDone = 0;
    static uint32_t rotateEarliestDone = 0;

    Position selfPos  = worldState->getSelfPosition();
    Position enemyPos = worldState->getEnemyPosition();  // sector detection

    // keep timers current
    turnTimer->setCurrentTime(time);
    backupTimer->setCurrentTime(time);

    // helper to know if we're touching the edge this tick
    auto onLineNow = [&](Position p){
        return p == Position::On_Line || p == Position::On_Line_Left || p == Position::On_Line_Right;
    };

    if (isTurning) {
        // Only allow enemy to cancel when safe (not on the line this tick)
        const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

        if (!enemyInterrupt) {
            // if we are in a line-save maneuver, cancel any aim latch
            latchActive = false;

            if (phase == Phase::BackingUp) {
                bool dwellSatisfied = (int32_t)(time - backupEarliestDone) >= 0;
                if (!backupTimer->getReady() || !dwellSatisfied) {
                    robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                    return;
                }
                phase = Phase::Rotating;
                turnTimer->setPreviousTime(time);
                rotateEarliestDone = time + MIN_ROTATE_DWELL_MS;   // start rotate dwell
            }

            if (phase == Phase::Rotating) {
                bool dwellSatisfied = (int32_t)(time - rotateEarliestDone) >= 0;
                if (!turnTimer->getReady() || !dwellSatisfied) {
                    if (turnDir == TurnDir::Left)  robotActions->drive(-ROTATE_SPEED, ROTATE_SPEED);
                    else                            robotActions->drive( ROTATE_SPEED, -ROTATE_SPEED);
                    return;
                }
                // finish
                isTurning = false;
                phase = Phase::Idle;
                turnDir = TurnDir::None;
            }
        } else {
            // Enemy visible & we're safely off the line: abort maneuver and attack
            isTurning = false;
            phase = Phase::Idle;
            turnDir = TurnDir::None;
            // fall through to enemy logic below
        }
    }

    if (!isTurning && pendingLine) {
        // Allow enemy to break the hold only when safe (not on line now)
        const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

        if (!enemyInterrupt) {
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
                backupEarliestDone = time + MIN_BACKUP_DWELL_MS;   // start backup dwell
                pendingLine = false;
                latchActive = false; // edge safety cancels aim latch
                robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                return;
            }

            if (time - pendingT0 >= BOTH_WINDOW_MS) {
                backupTimer->setTimeInterval(BACKUP_MS_SIDE);
                turnTimer->setTimeInterval(ROTATE_MS_SIDE);
                turnDir = pendingDir; // the side we latched
                isTurning = true;
                phase = Phase::BackingUp;
                backupTimer->setPreviousTime(time);
                backupEarliestDone = time + MIN_BACKUP_DWELL_MS;   // start backup dwell
                pendingLine = false;
                latchActive = false; // edge safety cancels aim latch
                robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                return;
            }
            // still waiting inside window
            robotActions->drive(0, 0);
            return;
        } else {
            // Enemy visible & safely off the line: drop the hold and attack
            pendingLine = false;
            // fall through to enemy logic
        }
    }

    if (!isTurning && !pendingLine) {
        if (selfPos == Position::On_Line) {
            backupTimer->setTimeInterval(BACKUP_MS_BOTH);
            turnTimer->setTimeInterval(ROTATE_MS_BOTH);
            turnDir = TurnDir::Right; // default on both
            isTurning = true;
            phase = Phase::BackingUp;
            backupTimer->setPreviousTime(time);
            backupEarliestDone = time + MIN_BACKUP_DWELL_MS;       // start backup dwell
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

    double rotSpeed     = 255.0;

    // create/maintain latch when we see Left/Right near the boundary
    if (!latchActive && (enemyPos == Position::Left || enemyPos == Position::Right)) {
        latchActive = true;
        latchDir    = (enemyPos == Position::Left) ? TurnDir::Left : TurnDir::Right;
        latchT0     = time;
        middleSeenT0 = -1;
    }

    // latched behavior (turn hard for a short dwell; break early if centered)
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

    if (enemyPos == Position::Flag_Left) {
        robotActions->drive(-255.0, 255.0);
    } else if (enemyPos == Position::Flag_Right) {
        robotActions->drive(255.0, -255.0);
    } else if (enemyPos == Position::Middle_Close) {
        robotActions->drive(255.0, 255.0);
    } else if (enemyPos == Position::Middle_Far) {
        robotActions->drive(150.0, 150.0);
    } else if (enemyPos == Position::Right_Middle_Close) {
        robotActions->drive(255.0, 200.0);

    } else if (enemyPos == Position::Left_Middle_Close) {
        robotActions->drive(200.0, 255.0);

    } else if (enemyPos == Position::Right_Middle) {
        robotActions->drive(255.0, -150.0);

    } else if (enemyPos == Position::Left_Middle) {
        robotActions->drive(-150.0, 255.0);

    } else if (enemyPos == Position::Right) {
        robotActions->drive(255.0, -255.0);

    } else if (enemyPos == Position::Left) {
        robotActions->drive(-255.0, 255.0);

    } else if (enemyPos == Position::None) {

        const int ZIGZAG_MS = 250;

        static bool zigLeft = false;
        static int ZIGZAG_INITIAL_MS = 0;

        if (ZIGZAG_INITIAL_MS == 0) ZIGZAG_INITIAL_MS = time; 
        if (time - ZIGZAG_INITIAL_MS >= ZIGZAG_MS) { 
            zigLeft = !zigLeft;
            ZIGZAG_INITIAL_MS = time;
        }

        if (zigLeft) {
            robotActions->drive(-100.0, 200.0);
        } else {
            robotActions->drive(200.0, -100.0);
        }

        return;
    }

}

bool RobotState::isMemeDone() const {
    return memeDone;
}

void RobotState::resetMatch() {
    memeDone = false;
    memeStep = 0;
}

void RobotState::memeRight(uint32_t time) {
    Position selfPos = worldState->getSelfPosition();

    if (selfPos == Position::On_Line ||
        selfPos == Position::On_Line_Left ||
        selfPos == Position::On_Line_Right) {
        memeDone = true;
        memeStarted = false;
        memeStep = 0;
        return;
    }

    memeTimer->setCurrentTime(time);

    switch (memeStep) {
        case 0: // initialize first move
            memeTimer->setPreviousTime(time);
            memeTimer->setTimeInterval(50);
            memeStep = 1;
            return;

        case 1: // turn right for 200 ms
            robotActions->drive(255, -255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(150);
                memeStep = 2;
            }
            return;

        case 2: // forward for 200 ms
            robotActions->drive(255, 255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(120);
                memeStep = 3;
            }
            return;

        case 3: // turn left for 300 ms
            robotActions->drive(-255, 255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(170);
                memeStep = 4;
            }
            return;

        case 4: // forward for 300 ms
            robotActions->drive(255, 255);
            if (memeTimer->getReady()) {
                memeDone = true;
                memeStep = 0;
            }
            return;
    }
}



void RobotState::memeLeft(uint32_t time) {
    Position selfPos = worldState->getSelfPosition();

    if (selfPos == Position::On_Line ||
        selfPos == Position::On_Line_Left ||
        selfPos == Position::On_Line_Right) {
        memeDone = true;
        memeStarted = false;
        memeStep = 0;
        return;
    }

    memeTimer->setCurrentTime(time);

    switch (memeStep) {
        case 0: // initialize first move
            memeTimer->setPreviousTime(time);
            memeTimer->setTimeInterval(50);
            memeStep = 1;
            return;

        case 1: // turn right for 200 ms
            robotActions->drive(-255, 255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(150);
                memeStep = 2;
            }
            return;

        case 2: // forward for 200 ms
            robotActions->drive(255, 255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(120);
                memeStep = 3;
            }
            return;

        case 3: // turn left for 300 ms
            robotActions->drive(255, -255);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(170);
                memeStep = 4;
            }
            return;

        case 4: // forward for 300 ms
            robotActions->drive(255, 255);
            if (memeTimer->getReady()) {
                memeDone = true;
                memeStep = 0;
            }
            return;
    }
}


void RobotState::slowTrackState(uint32_t time) {
    const int BACKUP_SPEED   = 200;
    const int ROTATE_SPEED   = 200;

    const int BACKUP_MS_SIDE = 200;
    const int BACKUP_MS_BOTH = 250;
    const int ROTATE_MS_SIDE = 80;
    const int ROTATE_MS_BOTH = 80;

    const int BOTH_WINDOW_MS = 20;
    const int MIN_BACKUP_DWELL_MS = 60;
    const int MIN_ROTATE_DWELL_MS = 80;

    // slow-track behavior timings
    const int INCH_PAUSE_MS   = 1000;
    const int INCH_FORWARD_MS = 500;

    static bool     pendingLine = false;
    static TurnDir  pendingDir  = TurnDir::None;
    static int      pendingT0   = 0;

    static uint32_t backupEarliestDone = 0;
    static uint32_t rotateEarliestDone = 0;

    // slow-track state
    enum class SlowTrackPhase {
        Pause,
        Forward
    };

    static SlowTrackPhase slowPhase = SlowTrackPhase::Pause;
    static uint32_t slowPhaseStart = 0;

    static int slowScanStep = 0;       // 0=L200, 1=R400, 2=L400, 3+=alternate 400
    static bool slowScanLeft = false;  // used after initial 3 scan steps
    static uint32_t slowScanStart = 0;

    static Position lastSlowEnemyPos = Position::None;

    Position selfPos  = worldState->getSelfPosition();
    Position enemyPos = worldState->getEnemyPosition();

    turnTimer->setCurrentTime(time);
    backupTimer->setCurrentTime(time);

    auto onLineNow = [&](Position p) {
        return p == Position::On_Line ||
               p == Position::On_Line_Left ||
               p == Position::On_Line_Right;
    };

    auto resetSlowTrackPattern = [&]() {
        slowPhase = SlowTrackPhase::Pause;
        slowPhaseStart = time;
        slowScanStep = 0;
        slowScanLeft = false;
        slowScanStart = time;
        lastSlowEnemyPos = Position::None;
    };

    // =========================================================
    // 1. LINE SAFETY / EDGE RECOVERY
    // =========================================================

    if (isTurning) {
        const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

        if (!enemyInterrupt) {
            if (phase == Phase::BackingUp) {
                bool dwellSatisfied = (int32_t)(time - backupEarliestDone) >= 0;
                if (!backupTimer->getReady() || !dwellSatisfied) {
                    robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                    return;
                }

                phase = Phase::Rotating;
                turnTimer->setPreviousTime(time);
                rotateEarliestDone = time + MIN_ROTATE_DWELL_MS;
            }

            if (phase == Phase::Rotating) {
                bool dwellSatisfied = (int32_t)(time - rotateEarliestDone) >= 0;
                if (!turnTimer->getReady() || !dwellSatisfied) {
                    if (turnDir == TurnDir::Left) {
                        robotActions->drive(-ROTATE_SPEED, ROTATE_SPEED);
                    } else {
                        robotActions->drive(ROTATE_SPEED, -ROTATE_SPEED);
                    }
                    return;
                }

                isTurning = false;
                phase = Phase::Idle;
                turnDir = TurnDir::None;

                resetSlowTrackPattern();
            }
        } else {
            isTurning = false;
            phase = Phase::Idle;
            turnDir = TurnDir::None;
        }
    }

    if (!isTurning && pendingLine) {
        const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

        if (!enemyInterrupt) {
            if (selfPos == Position::On_Line) {
                backupTimer->setTimeInterval(BACKUP_MS_BOTH);
                turnTimer->setTimeInterval(ROTATE_MS_BOTH);
                turnDir = TurnDir::Right;

                isTurning = true;
                phase = Phase::BackingUp;
                backupTimer->setPreviousTime(time);
                backupEarliestDone = time + MIN_BACKUP_DWELL_MS;
                pendingLine = false;

                robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                return;
            }

            if (time - pendingT0 >= BOTH_WINDOW_MS) {
                backupTimer->setTimeInterval(BACKUP_MS_SIDE);
                turnTimer->setTimeInterval(ROTATE_MS_SIDE);
                turnDir = pendingDir;

                isTurning = true;
                phase = Phase::BackingUp;
                backupTimer->setPreviousTime(time);
                backupEarliestDone = time + MIN_BACKUP_DWELL_MS;
                pendingLine = false;

                robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                return;
            }

            robotActions->drive(0, 0);
            return;
        } else {
            pendingLine = false;
        }
    }

    if (!isTurning && !pendingLine) {
        if (selfPos == Position::On_Line) {
            backupTimer->setTimeInterval(BACKUP_MS_BOTH);
            turnTimer->setTimeInterval(ROTATE_MS_BOTH);
            turnDir = TurnDir::Right;

            isTurning = true;
            phase = Phase::BackingUp;
            backupTimer->setPreviousTime(time);
            backupEarliestDone = time + MIN_BACKUP_DWELL_MS;

            resetSlowTrackPattern();

            robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
            return;
        }

        if (selfPos == Position::On_Line_Left) {
            pendingLine = true;
            pendingDir = TurnDir::Right;   // turn away from left edge
            pendingT0 = time;

            resetSlowTrackPattern();

            robotActions->drive(0, 0);
            return;
        }

        if (selfPos == Position::On_Line_Right) {
            pendingLine = true;
            pendingDir = TurnDir::Left;    // turn away from right edge
            pendingT0 = time;

            resetSlowTrackPattern();

            robotActions->drive(0, 0);
            return;
        }
    }

    // =========================================================
    // 2. SLOW-TRACK ENEMY HANDLING
    // =========================================================

    bool enemySeen = (enemyPos != Position::None);

    // Reset inch/scan patterns whenever enemy classification changes
    if (enemySeen && enemyPos != lastSlowEnemyPos) {
        slowPhase = SlowTrackPhase::Pause;
        slowPhaseStart = time;
        slowScanStep = 0;
        slowScanLeft = false;
        slowScanStart = time;
    }

    lastSlowEnemyPos = enemyPos;

    if (enemySeen) {
        // Very close -> full charge
        if (enemyPos == Position::Middle_Close) {
            robotActions->drive(255, 255);
            return;
        }

         if (enemyPos == Position::Right_Middle) {
            robotActions->drive(255, 255);
            return;
        }

        if (enemyPos == Position::Left_Middle) {
            robotActions->drive(255, 255);
            return;
        }

        // Side sectors -> rotate toward enemy
        if (enemyPos == Position::Right ||
            enemyPos == Position::Flag_Right) {
            robotActions->drive(150, -150);
            return;
        }

        if (enemyPos == Position::Left ||
            enemyPos == Position::Flag_Left) {
            robotActions->drive(-150, 150);
            return;
        }

   

        // Middle-ish -> inch forward slowly
        if (enemyPos == Position::Middle_Far ||
            enemyPos == Position::Right_Middle_Close ||
            enemyPos == Position::Left_Middle_Close) {

            if (slowPhase == SlowTrackPhase::Pause) {
                robotActions->drive(0, 0);

                if (time - slowPhaseStart >= INCH_PAUSE_MS) {
                    slowPhase = SlowTrackPhase::Forward;
                    slowPhaseStart = time;
                }
            } else {
                // slight steering bias if off-center
                if (enemyPos == Position::Left_Middle_Close) {
                    robotActions->drive(90, 130);
                } else if (enemyPos == Position::Right_Middle_Close) {
                    robotActions->drive(130, 90);
                } else {
                    robotActions->drive(110, 110);
                }

                if (time - slowPhaseStart >= INCH_FORWARD_MS) {
                    slowPhase = SlowTrackPhase::Pause;
                    slowPhaseStart = time;
                }
            }

            return;
        }

        // fallback if you add more positions later
        robotActions->drive(0, 0);
        return;
    }

    // =========================================================
    // 3. NO ENEMY -> SCAN BACK AND FORTH
    // =========================================================

    if (slowScanStep == 0) {
        robotActions->drive(-100, 100);   // left 200
        if (time - slowScanStart >= 100) {
            slowScanStep = 1;
            slowScanStart = time;
        }
        return;
    }

    if (slowScanStep == 1) {
        robotActions->drive(100, -100);   // right 400
        if (time - slowScanStart >= 250) {
            slowScanStep = 2;
            slowScanStart = time;
        }
        return;
    }

    if (slowScanStep == 2) {
        robotActions->drive(-100, 100);   // left 400
        if (time - slowScanStart >= 500) {
            slowScanStep = 3;
            slowScanLeft = false;         // next alternating step starts right
            slowScanStart = time;
        }
        return;
    }

    // alternate every 400 ms afterward
    if (slowScanLeft) {
        robotActions->drive(-100, 100);
    } else {
        robotActions->drive(100, -100);
    }

    if (time - slowScanStart >= 500) {
        slowScanLeft = !slowScanLeft;
        slowScanStart = time;
    }
}


// new proper zig/zag

// void RobotState::calculateState(uint32_t time) {
//     const int BACKUP_SPEED   = 200;
//     const int ROTATE_SPEED   = 200;

//     const int BACKUP_MS_SIDE = 200; 
//     const int BACKUP_MS_BOTH = 250;
//     const int ROTATE_MS_SIDE = 60;
//     const int ROTATE_MS_BOTH = 120;

//     // debounce window to decide "both" vs "side-only"
//     const int BOTH_WINDOW_MS = 20;

//     // --- latch tunables (turn-hold after Left/Right detection)
//     const int LATCH_MS = 30;              // hold hard turn briefly
//     const int MIDDLE_CONFIRM_MS = 20;     // see middle this long to break latch early

//     // --- NEW: anti-race minimum dwells to survive slow/jittery loops


//     // Debounce state (static locals: no header changes)
//     static bool     pendingLine = false;       // we saw a side hit and are waiting
//     static TurnDir  pendingDir  = TurnDir::None;
//     static int      pendingT0   = 0;

//     // Latch state
//     static bool     latchActive  = false;
//     static TurnDir  latchDir     = TurnDir::None;
//     static int      latchT0      = 0;
//     static int      middleSeenT0 = -1;

//     // --- NEW: phase dwell (anti-race) timestamps
//     static uint32_t backupEarliestDone = 0;
//     static uint32_t rotateEarliestDone = 0;

//     // ===== NEW: zig + rotate-finish linkage (no header changes) =====
//     static bool     zigLeft            = false;                // starts false
//     static bool     zigOverridePending = false;                // one-shot override after rotate
//     static TurnDir  lastRotateDir      = TurnDir::None;        // direction of last completed rotate
//     static int      ZIGZAG_INITIAL_MS  = 0;                    // moved out of None block

//     Position selfPos  = worldState->getSelfPosition();
//     Position enemyPos = worldState->getEnemyPosition();  // sector detection

//     // keep timers current
//     turnTimer->setCurrentTime(time);
//     backupTimer->setCurrentTime(time);

//     // helper to know if we're touching the edge this tick
//     auto onLineNow = [&](Position p){
//         return p == Position::On_Line || p == Position::On_Line_Left || p == Position::On_Line_Right;
//     };

//     // === Maneuver in progress ===
//     if (isTurning) {
//         // Only allow enemy to cancel when safe (not on the line this tick)
//         const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

//         if (!enemyInterrupt) {
//             // if we are in a line-save maneuver, cancel any aim latch
//             latchActive = false;

//             if (phase == Phase::BackingUp) {
//                 // --- NEW: enforce minimum dwell to avoid finishing in one coarse tick
//                 bool dwellSatisfied = (int32_t)(time - backupEarliestDone) >= 0;
//                 if (!backupTimer->getReady() || !dwellSatisfied) {
//                     robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
//                     return;
//                 }
//                 phase = Phase::Rotating;
//                 turnTimer->setPreviousTime(time);
//                 rotateEarliestDone = time;   // start rotate dwell
//             }

//             if (phase == Phase::Rotating) {
//                 // --- NEW: enforce minimum dwell to avoid rotate “instant finish”
//                 bool dwellSatisfied = (int32_t)(time - rotateEarliestDone) >= 0;
//                 if (!turnTimer->getReady() || !dwellSatisfied) {
//                     if (turnDir == TurnDir::Left)  robotActions->drive(-ROTATE_SPEED, ROTATE_SPEED);
//                     else                            robotActions->drive( ROTATE_SPEED, -ROTATE_SPEED);
//                     return;
//                 }
//                 // ===== finish =====
//                 lastRotateDir = turnDir;                     // remember actual rotate direction
//                 isTurning = false;
//                 phase = Phase::Idle;
//                 turnDir = TurnDir::None;

//                 // Prime next wander direction once, based on rotate
//                 zigOverridePending = (lastRotateDir == TurnDir::Left) || (lastRotateDir == TurnDir::Right);
//             }
//         } else {
//             // Enemy visible & we're safely off the line: abort maneuver and attack
//             isTurning = false;
//             phase = Phase::Idle;
//             turnDir = TurnDir::None;
//             // no zig priming on abort
//             // fall through to enemy logic below
//         }
//     }

//     // === Debounce window handling (only when not turning) ===
//     if (!isTurning && pendingLine) {
//         // Allow enemy to break the hold only when safe (not on line now)
//         const bool enemyInterrupt = (enemyPos != Position::None) && !onLineNow(selfPos);

//         if (!enemyInterrupt) {
//             // if both sensors detected during window -> commit as BOTH
//             if (selfPos == Position::On_Line) {
//                 // choose durations (BOTH) and direction default
//                 backupTimer->setTimeInterval(BACKUP_MS_BOTH);
//                 turnTimer->setTimeInterval(ROTATE_MS_BOTH);
//                 turnDir = TurnDir::Right; // consistent default for "both"
//                 // start maneuver
//                 isTurning = true;
//                 phase = Phase::BackingUp;
//                 backupTimer->setPreviousTime(time);
//                 backupEarliestDone = time;   // start backup dwell
//                 pendingLine = false;
//                 latchActive = false; // edge safety cancels aim latch
//                 robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
//                 return;
//             }
//             // if window expired -> commit as SIDE
//             if (time - pendingT0 >= BOTH_WINDOW_MS) {
//                 backupTimer->setTimeInterval(BACKUP_MS_SIDE);
//                 turnTimer->setTimeInterval(ROTATE_MS_SIDE);
//                 turnDir = pendingDir; // the side we latched
//                 isTurning = true;
//                 phase = Phase::BackingUp;
//                 backupTimer->setPreviousTime(time);
//                 backupEarliestDone = time;   // start backup dwell
//                 pendingLine = false;
//                 latchActive = false; // edge safety cancels aim latch
//                 robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
//                 return;
//             }
//             // still waiting inside window
//             robotActions->drive(0, 0);
//             return;
//         } else {
//             // Enemy visible & safely off the line: drop the hold and attack
//             pendingLine = false;
//             // fall through to enemy logic
//         }
//     }

//     // === New detection (no maneuver active and no pending) ===
//     if (!isTurning && !pendingLine) {
//         if (selfPos == Position::On_Line) {
//             // both at once -> commit immediately to BOTH
//             backupTimer->setTimeInterval(BACKUP_MS_BOTH);
//             turnTimer->setTimeInterval(ROTATE_MS_BOTH);
//             turnDir = TurnDir::Right; // default on both
//             isTurning = true;
//             phase = Phase::BackingUp;
//             backupTimer->setPreviousTime(time);
//             backupEarliestDone = time;       // start backup dwell
//             pendingLine = false;
//             latchActive = false; // edge safety cancels aim latch
//             robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
//             return;
//         }
//         if (selfPos == Position::On_Line_Left) {
//             // start debounce window for possible BOTH
//             pendingLine = true;
//             pendingDir  = TurnDir::Right; // turn away from left
//             pendingT0   = time;
//             robotActions->drive(0, 0);    // kill momentum while waiting
//             return;
//         }
//         if (selfPos == Position::On_Line_Right) {
//             pendingLine = true;
//             pendingDir  = TurnDir::Left;  // turn away from right
//             pendingT0   = time;
//             robotActions->drive(0, 0);
//             return;
//         }
//     }

//     // ====== ENEMY DETECTION (your exact speeds) ======
//     double rotSpeed     = 255.0;

//     // create/maintain latch when we see Left/Right near the boundary
//     if (!latchActive && (enemyPos == Position::Left || enemyPos == Position::Right)) {
//         latchActive = true;
//         latchDir    = (enemyPos == Position::Left) ? TurnDir::Left : TurnDir::Right;
//         latchT0     = time;
//         middleSeenT0 = -1;
//     }

//     // latched behavior (turn hard for a short dwell; break early if centered)
//     if (latchActive) {
//         // if any middle sector is seen, start/confirm early exit
//         bool middleNow =
//             (enemyPos == Position::Left_Middle) || (enemyPos == Position::Left_Middle_Close) ||
//             (enemyPos == Position::Right_Middle) || (enemyPos == Position::Right_Middle_Close) ||
//             (enemyPos == Position::Middle_Far)   || (enemyPos == Position::Middle_Close);

//         if (middleNow) {
//             if (middleSeenT0 < 0) middleSeenT0 = time;
//             if (time - middleSeenT0 >= MIDDLE_CONFIRM_MS) {
//                 latchActive = false; // hand back to normal logic
//             }
//         } else {
//             middleSeenT0 = -1; // reset confirmation timer
//         }

//         // timeout to avoid over-committing if we never see middle
//         if (time - latchT0 >= LATCH_MS) {
//             latchActive = false;
//         }

//         // while still latched, keep turning hard toward the side and return
//         if (latchActive) {
//             if (latchDir == TurnDir::Left)  robotActions->drive(-rotSpeed,  rotSpeed);
//             else                             robotActions->drive( rotSpeed, -rotSpeed);
//             return;
//         }
//         // if latch just ended, fall through to your normal enemy logic below
//     }

//     // === Your original enemy reaction logic ===
//     if (enemyPos == Position::Flag_Left) {
//         robotActions->drive(-255.0, 255.0);
//     } else if (enemyPos == Position::Flag_Right) {
//         robotActions->drive(255.0, -255.0);
//     } else if (enemyPos == Position::Middle_Close) {
//         robotActions->drive(255.0, 255.0);
//     } else if (enemyPos == Position::Middle_Far) {
//         robotActions->drive(150.0, 150.0);
//     } else if (enemyPos == Position::Right_Middle_Close) {
//         robotActions->drive(255.0, 200.0);

//     } else if (enemyPos == Position::Left_Middle_Close) {
//         robotActions->drive(200.0, 255.0);

//     } else if (enemyPos == Position::Right_Middle) {
//         robotActions->drive(255.0, 200.0);

//     } else if (enemyPos == Position::Left_Middle) {
//         robotActions->drive(200.0, 255.0);

//     } else if (enemyPos == Position::Right) {
//         robotActions->drive(255.0, -255.0);

//     } else if (enemyPos == Position::Left) {
//         robotActions->drive(-255.0, 255.0);

//     } else if (enemyPos == Position::None) {

//         const int ZIGZAG_MS = 250;

//         // Apply one-shot preference set by the last completed rotate.
//         if (zigOverridePending) {
//             zigLeft = (lastRotateDir == TurnDir::Left);  // Left rotate -> zig left first
//             zigOverridePending = false;
//             // Hold this chosen side for a full interval
//             ZIGZAG_INITIAL_MS = time;
//         }

//         if (ZIGZAG_INITIAL_MS == 0) ZIGZAG_INITIAL_MS = time; 
//         if (time - ZIGZAG_INITIAL_MS >= ZIGZAG_MS) { 
//             zigLeft = !zigLeft;
//             ZIGZAG_INITIAL_MS = time;
//         }

//         if (zigLeft) {
//             robotActions->drive(-100.0, 200.0);
//         } else {
//             robotActions->drive(200.0, -100.0);
//         }

//         return;
//     }

//     // === Default: cruise ===
// }
