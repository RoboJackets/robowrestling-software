#ifndef newRobot_h
#define newRobot_h

#include <graphics/Renderable.h>
#include <strategy/strategy.h>
#include <simulator/physics/RigidBody2d.h>
#include <memory>
#include <cmath>

class NewRobot : public Renderable { //abstract class of a robot
	public:
		//double x_pos_; //x position of the center of the robot relative to the top left corner of the window. +x is to the right
		//double y_pos_; //y position of the center of the robot relative to the top left corner of the window. +y is down
		//double angle_; //how much the robot is rotated from 0-2pi with 0 being "east"

		//double width_; //width of robot used for collision and ring out calculations. used as distance between wheels
		//double length_; //length of robot used for collision and ring out calculations

        RigidBody2d body_;

        double _cmToPixel;
        double _radius;
		double wheel_radius_; //radius of wheel in cm. used to convert angular velocity to distance traveled and angle change
		double left_wheel_velocity_; //robot's left wheel's current velocity used for collision calculations. radians/s
		double right_wheel_velocity_; //robot's right wheel's current velocity used for collision calculations. radians/s
		double max_wheel_velocity_; //maximum velocity the robot's wheels can achieve in radians/s
		double wheel_acceleration_; //rate at which the robot's wheels accelerates in radians/s^2
		double linear_velocity_; //linear velocity of the robot (for when it's being pushed) cm(window units)/s
		double velocity_dir_; //direction of robot's linear velocity. 0-2pi with 0 being "east"

		std::unique_ptr<Strategy> strat_;

        NewRobot(double x, double y, double angle, int dohyoRadius);
        void Render(sf::RenderWindow& window, const RenderPoint& point) override;

		//virtual std::vector<std::pair<double, double>> corners() = 0;	//returns the corners in x, y pairs in order selecting them
																//counter clockwise from the middle of the face of the robot
};
#endif
