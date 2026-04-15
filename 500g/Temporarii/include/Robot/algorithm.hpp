#include "Enumerations/AlgoLogs.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/SweepStates.hpp"
#include "Robot/robotActions.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/Timer.hpp"
#include "Sensors/lineSensor.hpp"

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

class Algorithm {
 private:
  RobotActions* action;
  Timer* timer;
  bool line;
  float* yaw;

  SweepState sweepState;
  float theta_entry;
  float theta_exit;
  float theta_target;

 public:
  Algorithm(RobotActions* action, Timer* timer, float* yaw_ptr);
  void Test();
  // Search Algos
  void search();
  void fryThem();
  void pingPong(OnLine line_state, AlgoLogs algo);

  void RunItDown(EnemyPositions pos, AlgoLogs algo);
  void TurnToEnemy(EnemyPositions pos);
  void SideStrike(EnemyPositions pos);
  void backTrack(OnLine line_state, AlgoLogs algo);
  void Strat2Sweep(bool midDetected);
  void evade();
  bool getTimer();
};

#endif