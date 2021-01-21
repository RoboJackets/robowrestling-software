#ifndef robotphysicsupdater_h
#define robotphysicsupdater_h

#include <cmath>
#include <memory>
#include <simulator/robot.h>

class RobotPhysicsUpdater {
	public: 
        RobotPhysicsUpdater();
	   
        void update(std::shared_ptr<Robot> r1, std::vector<double> r1_update, std::shared_ptr<Robot> r2, std::vector<double> r2_update); //overall update method that takes in the two robots and necessary information in the form of vectors
                                                                                                                                         //vectors contain in order left_wheel, right_wheel, duration

        void move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration); //takes in a robot, percentage power used on each wheel, and a duration in seconds

        void check_collision(); //uses given information to check if the robots will collide

        void collision(); //updates the position and velocities of the robots using collision logic
};

#endif
