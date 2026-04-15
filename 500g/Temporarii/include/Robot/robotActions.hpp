#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/PrevAction.hpp"
#include "Robot/motorDriver.hpp"

#ifndef ROBOTACTIONS_HPP
#define ROBOTACTIONS_HPP

class RobotActions {
 private:
  MotorDriver* flDriver;
  MotorDriver* frDriver;
  MotorDriver* blDriver;
  MotorDriver* brDriver;
  int speed;
  int curr_spd;

  PrevAction prev_action;

 public:
  RobotActions(MotorDriver*, MotorDriver*, MotorDriver*, MotorDriver*);
  void Attack(EnemyPositions pos);
  void Forward(int spd);
  void Backwards(int spd);
  void Left(int spd);
  void Right(int spd);
  void RampLeft(int max_spd);
  void RampRight(int max_spd);
  void ArcLeft(int spd);
  void ArcRight(int spd);
  void Circle();
};

#endif