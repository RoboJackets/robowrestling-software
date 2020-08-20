#include "robotphysicsupdater.h"

RobotPhysicsUpdater::RobotPhysicsUpdater() {}

RobotPhysicsUpdater::move_robot(Robot* r, int left_wheel, int right_wheel, int duration) {
	//calculate how fast the right wheel moves
	double right_velocity_increase = duration * r->wheel_acceleration;
	double right_new_velocity = r->right_wheel_velocity + right_velocity_increase;
	if (right_new_velocity > r->max_wheel_velocity) {
		right_new_velocity = r->max_wheel_velocity;
	}
	double average_right_velocity = (right_new_velocity + r->right_wheel_velocity) / 2;
	r->right_wheel_velocity = right_new_velocity;
	//calculate how fast the left wheel moves
	double left_velocity_increase = duration * r->wheel_acceleration;
	double left_new_velocity = r->leftt_wheel_velocity + left_velocity_increase;
	if (left_new_velocity > r->max_wheel_velocity) {
		left_new_velocity = r->max_wheel_velocity;
	}
	double average_left_velocity = (left_new_velocity + r->left_wheel_velocity) / 2;
	r->left_wheel_velocity = left_new_velocity;

	if (average_right_velocity > average_left_velocity) {
		double outer_travel_radius = r->width / (1 - (average_left_velocity / average_right_velocity));
		double inner_travel_radius = outer_travel_radius - r->width;
	} else if (average_left_velocity > average_right_velocity) {
		double outer_travel_radius = r->width / (1 - (average_right_velocity / average_left_velocity));
		double inner_travel_radius = outer_travel_radius - r->width;
	} else {
		double distance_traveled = average_right_velocity * duration;
		
	}
}