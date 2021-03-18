#ifndef robot_h
#define robot_h

#include <strategy/strategy.h>
#include <memory>
#include <cmath>

class Robot { //abstract class of a robot
	public:
		double x_pos_; //x position of the center of the robot relative to the top left corner of the window. +x is to the right
		double y_pos_; //y position of the center of the robot relative to the top left corner of the window. +y is down
		double angle_; //how much the robot is rotated from 0-2pi with 0 being "east"
		
		double width_; //width of robot used for collision and ring out calculations. used as distance between wheels
		double length_; //length of robot used for collision and ring out calculations
		int plow_angle_; //angle of the plow in radians with 0 being flat
		
		double wheel_radius_; //radius of wheel in m. used to convert angular velocity to distance traveled and angle change
		double left_wheel_velocity_; //robot's left wheel's current velocity used for collision calculations. radians/s
		double right_wheel_velocity_; //robot's right wheel's current velocity used for collision calculations. radians/s
		double max_wheel_velocity_; //maximum velocity the robot's wheels can achieve
		double wheel_acceleration_; //rate at which the robot's wheels accelerates in radians/s^2
		double linear_velocity_; //linear velocity of the robot (for when it's being pushed) cm(window units)/s
		double velocity_dir_; //direction of robot's linear velocity. 0-2pi with 0 being "east"

		double static_friction_; //coefficient of friction for when the robot is static (in the direction of the force)
		double rolling_friction_; //coefficient of friction for when the robot is rolling (in the direction of the force)
		double sliding_friction_; //coefficient of friction for when the robot is sliding (in the direction of the force)

		std::unique_ptr<Strategy> strat_;

		virtual std::vector<std::pair<double, double>> corners() = 0;	//returns the corners in x, y pairs in order selecting them
																//counter clockwise from the middle of the face of the robot
};
#endif