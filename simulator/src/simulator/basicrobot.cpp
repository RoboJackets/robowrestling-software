#include <simulator/basicrobot.h>

BasicRobot::BasicRobot(double x_pos, double y_pos, double angle) {
	x_pos_ = x_pos;
	y_pos_ = y_pos;
	angle_ = angle;

	width_ = 30;
	length_ = 30;

	wheel_radius_ = 1;
	left_wheel_velocity_ = 0;
	right_wheel_velocity_ = 0;
	max_wheel_velocity_ = 8;
	wheel_acceleration_ = 1;

	strat_ = std::make_unique<SlammyWhammy>();
}
