#ifndef testphysicsupdater_h
#define testphysicsupdater_h

#include <cmath>
#include <memory>
#include <simulator/robots/robot.h>

class TestPhysicsUpdater {
	public: 
        TestPhysicsUpdater();
	   
        void update(std::shared_ptr<Robot> r1, std::vector<int> r1_update, std::shared_ptr<Robot> r2, std::vector<int> r2_update, double duration); //overall update method that takes in the two robots and necessary information in the form of vectors
                                                                                                                                         //vectors contain in order left_wheel, right_wheel, other robot specific update information (may be none)

        void move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration); //takes in a robot, percentage power used on each wheel, and a duration in seconds

        bool check_collision(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2); //uses given information to check if the robots will collide using Seperating Axis Theorem

        void collision_handler(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2); //updates the position and velocities of the robots using collision logic
};

#endif
