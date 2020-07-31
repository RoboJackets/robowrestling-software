#include "basicrobot.h"

BasicRobot::BasicRobot(double x, double y, double angle) {
	this.x_pos = x;
	this.y_pos = y;
	this.angle= angle;

	this.width = 30;
	this.length = 30;

	this.velocity = 5;
};