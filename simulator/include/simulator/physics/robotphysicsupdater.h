#ifndef robotphysicsupdater_h
#define robotphysicsupdater_h

#include <cmath>
#include <memory>
#include <simulator/robots/robot.h>

#define pdd std::pair<double,double>

class RobotPhysicsUpdater {
	public: 
        RobotPhysicsUpdater();
	   
        void update(std::shared_ptr<Robot> r1, std::vector<int> r1_update, std::shared_ptr<Robot> r2, std::vector<int> r2_update, double duration); //overall update method that takes in the two robots and necessary information in the form of vectors
                                                                                                                                         //vectors contain in order left_wheel, right_wheel, other robot specific update information (may be none)

        void move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration); //takes in a robot, percentage power used on each wheel, and a duration in seconds

        bool check_collision(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2); //uses given information to check if the robots will collide using Seperating Axis Theorem

        void collision_handler(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2); //updates the position and velocities of the robots using collision logic

        private:
        void sat_test(pdd normal_axis, std::vector<pdd> corners, double& min_along, double& max_along); //performs the sat_test for overlaps

        double dot_product(pdd first, pdd second); //computes dot product between to coordinates

        bool overlaps(double min_1, double max_1, double min_2, double max_2);

        bool is_between_ordered(double val, double lower_bound, double upper_bound);

        private: 
        double compute_wheel_velocity(std::shared_ptr<Robot> robot, double wheel_ds, double current_vel, double duration); 

};

#endif
