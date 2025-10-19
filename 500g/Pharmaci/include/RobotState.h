#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "WorldState.h"
#include "RobotActions.h"
#include "Timer.h"

enum class TurnDir { Left, Right, None };
enum class Phase   { Idle, BackingUp, Rotating };

class RobotState {
  private:
    WorldState*   worldState;
    RobotActions* robotActions;
    MotorDriver*  leftMotorDriver;
    MotorDriver*  rightMotorDriver;

    Timer* turnTimer;
    Timer* backupTimer;

    bool    isTurning = false;
    Phase   phase     = Phase::Idle;
    TurnDir turnDir   = TurnDir::None;

  public:
    RobotState(WorldState* worldStatePtr,
               RobotActions* robotActionsPtr,
               MotorDriver* leftMotorDriverPtr,
               MotorDriver* rightMotorDriverPtr);

    void calculateState();
    void calculateState(uint32_t time);
};

#endif
