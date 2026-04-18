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
    Timer* memeTimer;
    

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
    void turretState();
    void antiPassive(uint32_t time);
    void memeRight(uint32_t time);
    void memeLeft(uint32_t time);
    void optimalStrategy(u_int32_t time);

    void resetMatch();

    bool isMemeDone() const;

    int servo = 90;

private:
    bool memeDone = false;
    bool memeStarted = false;
    int memeStep = 0;


};

#endif