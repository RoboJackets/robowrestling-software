#include <simulator/basicrobot.h>

BasicRobot::BasicRobot(double x, double y, double a) {
	x_pos = x;
	y_pos = y;
	angle = a;

	width = 30;
	length = 30;

	wheel_radius = 1;
	left_wheel_velocity = 0;
	right_wheel_velocity = 0;
	max_wheel_velocity = 8;
	wheel_acceleration = 1;
}
