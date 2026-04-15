#include <RobotState.h>
#include <Arduino.h>

RobotState::RobotState(WorldState* worldStatePtr, RobotActions* robotActionsPtr,
                       MotorDriver* leftMotorDriverPointer, MotorDriver* rightMotorDriverPointer) {
    worldState = worldStatePtr;
    robotActions = robotActionsPtr;
    leftMotorDriver = leftMotorDriverPointer;
    rightMotorDriver = rightMotorDriverPointer;

    turnTimer = new Timer();
    turnTimer->setTimeInterval(300);

    backupTimer = new Timer();
    backupTimer->setTimeInterval(300);

    isTurning = false;
    phase = Phase::Idle;
    turnDir = TurnDir::None;
}

// void RobotState::calculateState(u_int32_t time) {
//     robotActions->drive(0, 100);
// }

void RobotState::calculateState(uint32_t time) {

    const int BACKUP_SPEED = 150;
    const int TURN_SPEED   = 150;

    const int BACKUP_MS    = 250;
    const int TURN_MS      = 100;
    const int BOTH_TURN_MS = 60;

    const int ZIGZAG_MS = 300;

    static bool zigLeft = false;
    static int ZIGZAG_INITIAL_MS = 0;

    Position selfPos  = worldState->getSelfPosition();
    Position enemyPos = worldState->getEnemyPosition();

    backupTimer->setCurrentTime(time);
    turnTimer->setCurrentTime(time);

    // =========================
    // 1. Line-escape maneuver
    // =========================
    if (isTurning) {
        if (phase == Phase::BackingUp) {
            if (!backupTimer->getReady()) {
                if (turnDir == TurnDir::Right) {
                    // curved backup away from left edge
                    robotActions->drive(-80, -120);
                } else if (turnDir == TurnDir::Left) {
                    // curved backup away from right edge
                    robotActions->drive(-120, -80);
                } else {
                    // straight backup if both sensors hit
                    robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
                }
                return;
            }

            phase = Phase::Rotating;
            turnTimer->setPreviousTime(time);
        }

        if (phase == Phase::Rotating) {
            if (!turnTimer->getReady()) {
                if (turnDir == TurnDir::Left) {
                    robotActions->drive(-TURN_SPEED, TURN_SPEED);
                } else {
                    robotActions->drive(TURN_SPEED, -TURN_SPEED);
                }
                return;
            }

            isTurning = false;
            phase = Phase::Idle;
            turnDir = TurnDir::None;

            // restart zigzag cleanly after escape
            ZIGZAG_INITIAL_MS = time;
        }
    }

    // =========================
    // 2. Start line-escape if line seen
    // =========================
    if (selfPos == Position::On_Line_Left) {
        isTurning = true;
        phase = Phase::BackingUp;
        turnDir = TurnDir::Right;
        backupTimer->setTimeInterval(BACKUP_MS);
        turnTimer->setTimeInterval(TURN_MS);
        backupTimer->setPreviousTime(time);

        robotActions->drive(-80, -120);
        return;
    }

    if (selfPos == Position::On_Line_Right) {
        isTurning = true;
        phase = Phase::BackingUp;
        turnDir = TurnDir::Left;
        backupTimer->setTimeInterval(BACKUP_MS);
        turnTimer->setTimeInterval(TURN_MS);
        backupTimer->setPreviousTime(time);

        robotActions->drive(-120, -80);
        return;
    }

    if (selfPos == Position::On_Line) {
        isTurning = true;
        phase = Phase::BackingUp;
        turnDir = TurnDir::Right; // default
        backupTimer->setTimeInterval(BACKUP_MS);
        turnTimer->setTimeInterval(BOTH_TURN_MS);
        backupTimer->setPreviousTime(time);

        robotActions->drive(-BACKUP_SPEED, -BACKUP_SPEED);
        return;
    }

    // =========================
    // 3. Enemy logic
    // =========================
    if (enemyPos == Position::Flag_Left) {
        robotActions->drive(-255.0, 255.0);
    } else if (enemyPos == Position::Flag_Right) {
        robotActions->drive(255.0, -255.0);
    }
    else if (enemyPos == Position::Middle_Close || enemyPos == Position::Middle_Far) {
        robotActions->drive(255, 255);
        return;

    } 

    else if (enemyPos == Position::Middle_Far) {
        robotActions->drive(100, 100);
        return;
    }
    
    else if (enemyPos == Position::Right_Middle_Close) {
        robotActions->drive(255, 200);
        return;

    } else if (enemyPos == Position::Left_Middle_Close) {
        robotActions->drive(200, 255);
        return;

    } else if (enemyPos == Position::Right_Middle) {
        robotActions->drive(255, 150);
        return;

    } else if (enemyPos == Position::Left_Middle) {
        robotActions->drive(150, 255);
        return;

    } else if (enemyPos == Position::Right) {
        robotActions->drive(150, -150);
        return;

    } else if (enemyPos == Position::Left) {
        robotActions->drive(-150, 150);
        return;
    }

    // =========================
    // 4. No enemy -> zigzag wander
    // =========================
    if (ZIGZAG_INITIAL_MS == 0) ZIGZAG_INITIAL_MS = time;

    if (time - ZIGZAG_INITIAL_MS >= ZIGZAG_MS) {
        zigLeft = !zigLeft;
        ZIGZAG_INITIAL_MS = time;
    }

    if (zigLeft) {
        robotActions->drive(-60.0, 100.0);
    } else {
        robotActions->drive(100.0, -60.0);
    }
}