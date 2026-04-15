#include "Robot/robotState.hpp"

#include "Enumerations/AlgoLogs.hpp"
#include "Robot/algorithm.hpp"

// Tempi's Home :)
RobotState::RobotState(WorldState* world, Algorithm* algo) {
  this->world = world;
  this->algo = algo;
  this->prevAlgo = NoneAlgo;
  this->enemyPrev = EnemyNone;
  this->hasEvaded = false;
  this->hasWaited = 0;
  this->bnsTimer = new Timer(millis());
}

// Selecting Algo 🌀🔄
void RobotState::runAlgorithm(int strat_num) {
  // Grab line_state for ease of use
  OnLine line_state = world->getIsOnLine();

  // Decode strat (MODIFY for actual strategy name)
  Strategy strat = DefaultStrat;

  if (strat_num == 0) {
    strat = Strat0;
  } else if (strat_num == 1) {
    strat = Strat1;
  } else if (strat_num == 2) {
    strat = Strat2;
  } else if (strat_num == 3) {
    strat = Strat3;
  } else {
    strat = DefaultStrat;
  }

  // if (strat == Strat2) {
  //     bool midDetected = (world->getEnemyPosition() == EnemyFront);
  //     algo->Strat2Sweep(midDetected);
  //     return;
  // }
  switch (strat) {  // Switch 1 LOW, Switch 2 LOW
    case (Strat0):
      // Check expiration
      if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
      }

      // algo->fryThem();
      // prevAlgo = StirFry;
      // return;

      // OVERRIDE: ALWAYS ATTACK IF ENEMY IS SEEN MID
      if (world->getEnemyPosition() == EnemyFront) {
        algo->RunItDown(world->getEnemyPosition(), prevAlgo);
        prevAlgo = RunItDownAlgo;
        return;
      }

      // Enemy is in sights
      if (world->getEnemyPosition() == EnemyFL ||
          world->getEnemyPosition() == EnemyFR ||
          world->getEnemyPosition() == EnemyLeft ||
          world->getEnemyPosition() == EnemyRight) {
        algo->TurnToEnemy(world->getEnemyPosition());
        enemyPrev = world->getEnemyPosition();
        prevAlgo = Turn;
        return;
      }

      // Run remaining queued of Turn
      if (prevAlgo == Turn) {
        algo->TurnToEnemy(enemyPrev);
        return;
      }

      // Line Check First
      if (line_state == LineFL) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFL;
        return;
      } else if (line_state == LineFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFR;
        return;
      } else if (line_state == LineBL || line_state == LineBR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
        return;
      }

      // Run queued algo
      if (prevAlgo == BTFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFR;
        return;
      } else if (prevAlgo == BTFL) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFL;
        return;
      } else if (prevAlgo == BTBackward) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
        return;
      } else if (prevAlgo == StirFry) {
        algo->fryThem();
        prevAlgo = StirFry;
        return;
      } else {
        // algo->search();
        // prevAlgo = Search;
        algo->fryThem();
        prevAlgo = StirFry;
        return;
      }
      break;

      // One Time Evasion Strat
    case (Strat1):  // Switch 1 High, Switch 2 LOW
      // Mark evade as done once
      if (prevAlgo == Evade && !world->getAllFrontActive()) {
        hasEvaded = true;
      }

      if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
      }

      // Evade if all 3 front sensors fire
      if (!hasEvaded && world->getAllFrontActive()) {
        algo->evade();
        prevAlgo = Evade;
        return;
      }

      // Only Mid fires, Run it Down
      if (world->getEnemyPosition() == EnemyFront) {
        algo->RunItDown(world->getEnemyPosition(), prevAlgo);
        prevAlgo = RunItDownAlgo;
        return;
      }

      // Turn to face enemy after evading
      if (world->getEnemyPosition() == EnemyRight ||
          world->getEnemyPosition() == EnemyFR) {
        algo->TurnToEnemy(world->getEnemyPosition());
        enemyPrev = world->getEnemyPosition();
        prevAlgo = Turn;
        return;
      } else if (world->getEnemyPosition() == EnemyLeft ||
                 world->getEnemyPosition() == EnemyFL) {
        algo->TurnToEnemy(world->getEnemyPosition());
        enemyPrev = world->getEnemyPosition();
        prevAlgo = Turn;
        return;
      }
      // Continue queued turn
      if (prevAlgo == Turn) {
        algo->TurnToEnemy(enemyPrev);
        return;
      }

      algo->search();
      prevAlgo = Search;

      break;

    case (Strat2):  // Switch 1 LOW, Switch 2 HIGH
      if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
      }

      // OVERRIDE: ALWAYS ATTACK IF ENEMY IS SEEN MID
      if (world->getEnemyPosition() == EnemyFront) {
        algo->RunItDown(world->getEnemyPosition(), prevAlgo);
        prevAlgo = RunItDownAlgo;
        return;
      }

      // Enemy is in sights
      if (world->getEnemyPosition() == EnemyFL ||
          world->getEnemyPosition() == EnemyFR ||
          world->getEnemyPosition() == EnemyLeft ||
          world->getEnemyPosition() == EnemyRight) {
        algo->TurnToEnemy(world->getEnemyPosition());
        enemyPrev = world->getEnemyPosition();
        prevAlgo = Turn;
        return;
      }

      // Run remaining queued of Turn
      if (prevAlgo == Turn) {
        algo->TurnToEnemy(enemyPrev);
        return;
      }

      if (prevAlgo == pingPongR || line_state == LineFL) {
        algo->pingPong(line_state, prevAlgo);
        prevAlgo = pingPongR;
        return;
      } else if (prevAlgo == pingPongL || line_state == LineFR) {
        algo->pingPong(line_state, prevAlgo);
        prevAlgo = pingPongL;
        return;
      } else {
        algo->pingPong(line_state, prevAlgo);
        prevAlgo = pingPongF;
      }
      break;

    case (Strat3):  // Switch 1 HIGH, Switch 2 HIGH
      if (hasWaited == 0) { 
        bnsTimer->startTimer(1500);
        hasWaited = 1;
      }
      if (bnsTimer->getDuration() > 0) {
        return;
      }

      // Check expiration
      if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
      }

      // Line Check First
      if (line_state == LineFL || prevAlgo == BTFL) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFL;
        return;
      } else if (line_state == LineFR || prevAlgo == BTFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFR;
        return;
      } else if (line_state == LineBL || line_state == LineBR ||
                 prevAlgo == BTBackward) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
        return;
      }

      // OVERRIDE: ALWAYS ATTACK IF ENEMY IS SEEN MID
      if (world->getEnemyPosition() == EnemyFront) {
        algo->RunItDown(world->getEnemyPosition(), prevAlgo);
        prevAlgo = RunItDownAlgo;
        return;
      }

      // Enemy is in sights
      if (world->getEnemyPosition() == EnemyFL ||
          world->getEnemyPosition() == EnemyFR ||
          world->getEnemyPosition() == EnemyLeft ||
          world->getEnemyPosition() == EnemyRight) {
        algo->TurnToEnemy(world->getEnemyPosition());
        enemyPrev = world->getEnemyPosition();
        prevAlgo = Turn;
        return;
      }

      // Run remaining queued of Turn
      if (prevAlgo == Turn) {
        algo->TurnToEnemy(enemyPrev);
        return;
      }

      algo->fryThem();
      prevAlgo = StirFry;
      break;
    default:
      return;
  }
}