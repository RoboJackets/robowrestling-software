#include "Enumerations/AlgoLogs.hpp"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/Strategies.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Robot/algorithm.hpp"
#include "Sensors/WorldState.hpp"
#include "Sensors/Timer.hpp"

#ifndef ROBOTSTATE_HPP
#define ROBOTSTATE_HPP

class RobotState {
 private:
  WorldState* world;
  Algorithm* algo;
  AlgoLogs prevAlgo;
  EnemyPositions enemyPrev;
  Timer* bnsTimer;
  bool hasEvaded;
  int hasWaited;

 public:
  RobotState(WorldState* world, Algorithm* algo);
  void runAlgorithm(int strat);
};

#endif