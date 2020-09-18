#ifndef robotphysicsupdater_h
#define robotphysicsupdater_h

#include <cmath>
#include "../../robot.h"

class RobotPhysicsUpdater {
	public: RobotPhysicsUpdater();
	void move_robot(Robot* r, double left_wheel, double right_wheel, double duration); //takes in a robot, percentage power used on each wheel, and a duration in seconds
};

#endif
