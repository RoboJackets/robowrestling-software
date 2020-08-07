#include "basicrobot.h"

BasicRobot::BasicRobot(double x, double y, double angle) {
	x_pos = x;
	y_pos = y;
	angle = angle;

	width = 30;
	length = 30;

	velocity = 5;
}