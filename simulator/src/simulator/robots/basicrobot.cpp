#include <simulator/robots/basicrobot.h>

BasicRobot::BasicRobot(double x_pos, double y_pos, double angle) {
	x_pos_ = x_pos;
	y_pos_ = y_pos;
	angle_ = angle;

	width_ = 30;
	length_ = 30;

	wheel_radius_ = 20;
	left_wheel_velocity_ = 0;
	right_wheel_velocity_ = 0;
	max_wheel_velocity_ = 8;
	wheel_acceleration_ = 1;
	linear_velocity_ = 0;
	velocity_dir_ = 0;

	strat_ = std::make_unique<SlammyWhammy>();
}

std::vector<std::pair<double, double>> BasicRobot::corners() {
	auto ret = std::vector<std::pair<double, double>>();
	double shift_magnitude = sqrt(pow(this->width_/2, 2) + pow(this->length_/2, 2)); //distace from the center of the robot to a corner
	for (double i = 1; i <= 7; i+=2) {
		double x = this->x_pos_ + shift_magnitude*cos(this->angle_ + i/4 * M_PI);
		double y = this->y_pos_ + shift_magnitude*sin(this->angle_ + i/4 * M_PI);
		ret.push_back(std::make_pair(x, y));
	}

	return ret;
}
