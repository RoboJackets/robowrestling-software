#ifndef robot_h
#define robot_h

#include <strategy/strategy.h>
#include <memory>

class Robot { //abstract class of a robot
	public:
		double x_pos; //x position of the center of the robot relative to the top left corner of the window. +x is to the right
		double y_pos; //y position of the center of the robot relative to the top left corner of the window. +y is down
		double angle; //how much the robot is rotated from 0-2pi with 0 being "north"
		
		double width; //width of robot used for collision and ring out calculations. used as distance between wheels
		double length; //length of robot used for collision and ring out calculations
		
		double wheel_radius; //radius of wheel in m. used to convert angular velocity to distance traveled and angle change
		double left_wheel_velocity; //robot's left wheel's current velocity used for collision calculations. radians/s?
		double right_wheel_velocity; //robot's right wheel's current velocity used for collision calculations. radians/s?
		double max_wheel_velocity; //maximum velocity the robot's wheels can achieve
		double wheel_acceleration; //rate at which the robot's wheels accelerates in radians/s^2

		std::unique_ptr<Strategy> strat_;
};
#endif