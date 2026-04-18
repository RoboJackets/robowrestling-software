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

    memeTimer = new Timer();


    servo = 90;
    
    

}

void RobotState::turretState() {
    Position enemyPosition = worldState->getEnemyPosition();
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


bool RobotState::isMemeDone() const {
    return memeDone;
}

void RobotState::resetMatch() {
    memeDone = false;
    memeStep = 0;
}

void RobotState::optimalStrategy(u_int32_t time) {
    servo = 0;
    Position selfPos = worldState->getSelfPosition();
    Position enemyPos = worldState->getEnemyPosition();

    if (enemyPos == Position::Middle_Close ||
        enemyPos == Position::Left ||
        enemyPos == Position::Flag_Left ||
        enemyPos == Position::Left_Middle_Close ||
        enemyPos == Position::Left_Middle ||
        enemyPos == Position::Middle_Far ||
        enemyPos == Position::Flag_Right || 
        enemyPos == Position::Right_Middle ||
        enemyPos == Position::Right_Middle_Close
        
    ) {
        memeDone = true;
        memeStarted = false;
        memeStep = 0;
        return;
    }

    memeTimer->setCurrentTime(time);
    int rotSpeed = 80;
    int timeInterval = 200;
    switch (memeStep) {
        case 0:
            memeTimer->setPreviousTime(time);
            memeTimer->setTimeInterval(timeInterval);
            memeStep = 1;
            return;

        case 1:
            robotActions->drive(-rotSpeed, rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 2;
            }
            return;

        case 2:
            robotActions->drive(rotSpeed, -rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 3;
            }
            return;

        case 3:
            robotActions->drive(-rotSpeed, rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 4;
            }
            return;

        case 4:
            robotActions->drive(rotSpeed, -rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 5;
            }
            return;

        case 5:
            robotActions->drive(-rotSpeed, rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 6;
            }
            return;
            
        case 6:
            robotActions->drive(rotSpeed, -rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 7;
            }
            return;

        case 7:
            robotActions->drive(-rotSpeed, rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 8;
            }
            return;

        case 8:
            robotActions->drive(rotSpeed, -rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 9;
            }
            return;

        case 9:
            robotActions->drive(-rotSpeed, rotSpeed);
            if (memeTimer->getReady()) {
                memeTimer->setPreviousTime(time);
                memeTimer->setTimeInterval(timeInterval);
                memeStep = 10;
            }
            return;
        
        case 10:
            robotActions->drive(rotSpeed, -rotSpeed);
            if (memeTimer->getReady()) {
                memeDone = true;
                memeStep = 0;
            }
            return;

    }
}

void RobotState::memeRight(uint32_t time) {
    servo = 180;
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
                memeTimer->setTimeInterval(170);
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
    servo = 0;
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
                memeTimer->setTimeInterval(170);
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
        servo = 180;
        robotActions->drive(-255.0, 255.0);
        return;
    } else if (enemyPos == Position::Flag_Right) {
        servo = 0;
        robotActions->drive(255.0, -255.0);
        return;
    }
    else if (enemyPos == Position::Middle_Close) {
        robotActions->drive(255, 255);
        return;

    } 

    else if (enemyPos == Position::Middle_Far) {
        robotActions->drive(150, 150);
        return;
    }
    
    else if (enemyPos == Position::Right_Middle_Close) {
        servo = 0;
        robotActions->drive(255, 200);
        return;

    } else if (enemyPos == Position::Left_Middle_Close) {
        servo = 180;
        robotActions->drive(200, 255);
        return;

    } else if (enemyPos == Position::Right_Middle) {
        servo = 0;
        robotActions->drive(255, 150);
        return;

    } else if (enemyPos == Position::Left_Middle) {
        servo = 180;
        robotActions->drive(150, 255);
        return;

    } else if (enemyPos == Position::Right) {
        servo = 0;
        robotActions->drive(150, -150);
        return;

    } else if (enemyPos == Position::Left) {
        servo = 180;
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