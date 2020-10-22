#ifndef robotphysicsupdater_h
#define robotphysicsupdater_h

#include <cmath>
#include <memory>
#include <simulator/robot.h>

class RobotPhysicsUpdater {
	public: RobotPhysicsUpdater();
	void move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration); //takes in a robot, percentage power used on each wheel, and a duration in seconds
};

#endif
