#include <simulator/physics/robotphysicsupdater.h>

RobotPhysicsUpdater::RobotPhysicsUpdater() {

}

void RobotPhysicsUpdater::move_robot(Robot* r, double left_wheel, double right_wheel, double duration) {
	//calculate how fast the right wheel moves
	double right_velocity_increase = duration * r->wheel_acceleration * (right_wheel/100);
	double right_new_velocity = r->right_wheel_velocity + right_velocity_increase;
	if (right_new_velocity > r->max_wheel_velocity) {
		right_new_velocity = r->max_wheel_velocity;
	}
	double average_right_velocity = (right_new_velocity + r->right_wheel_velocity) / 2;
	r->right_wheel_velocity = right_new_velocity;
	//calculate how fast the left wheel moves
	double left_velocity_increase = duration * r->wheel_acceleration;
	double left_new_velocity = r->left_wheel_velocity + left_velocity_increase;
	if (left_new_velocity > r->max_wheel_velocity) {
		left_new_velocity = r->max_wheel_velocity;
	}
	double average_left_velocity = (left_new_velocity + r->left_wheel_velocity) / 2;
	r->left_wheel_velocity = left_new_velocity;

	if (average_right_velocity > average_left_velocity) { //swing turn right
		double right_linear_velocity = average_right_velocity * r->wheel_radius;
		double left_linear_velocity = average_left_velocity * r->wheel_radius;
		double curvature_radius = ((right_linear_velocity * r->width)/(right_linear_velocity - left_linear_velocity) - 1/2 * r->width);
		double average_linear_velocity = (right_linear_velocity+left_linear_velocity)/2;
		double distance_traveled = average_linear_velocity * duration;
		double angle_change = (-1 * distance_traveled) / curvature_radius; //in radians
		double x_change = curvature_radius * sin(angle_change);
		double y_change = (-1 * curvature_radius) * (1-cos(angle_change));
		r->x_pos += x_change;
		r->y_pos += y_change;
		r->angle += angle_change;
	} else if (average_left_velocity > average_right_velocity) { //swing turn left
		double right_linear_velocity = average_right_velocity * r->wheel_radius;
		double left_linear_velocity = average_left_velocity * r->wheel_radius;
		double curvature_radius = ((left_linear_velocity * r->width)/(left_linear_velocity - right_linear_velocity) - 1/2 * r->width);
		double average_linear_velocity = (right_linear_velocity+left_linear_velocity)/2;
		double distance_traveled = average_linear_velocity * duration;
		double angle_change = distance_traveled / curvature_radius; //in radians
		double x_change = curvature_radius * sin(angle_change);
		double y_change = (-1 * curvature_radius) * (1-cos(angle_change));
		r->x_pos += x_change;
		r->y_pos += y_change;
		r->angle += angle_change;
	} else { //drive straight
		double distance_traveled = average_right_velocity * duration * r->wheel_radius;
		double x_change = distance_traveled * cos(r->angle);
		double y_change = distance_traveled * sin(r->angle);
		r->x_pos += x_change;
		r->y_pos += y_change;
	}
}
// R = <(V2 * X) / (V2 - V1) - 1/2 * X> in the y_hat direction
// 7:34
// R = radius of curvature
// 7:35
// V1 and V2 = the linear velocities of the wheel on the contact point
// 7:35
// V1 and V2 = angular velocity * radius of wheel
// 7:35
// X = distance between the two wheels
// 7:36
// y_hat direction = a relative coordinate system defined by the line of intersection between the wheel centers

//if we make the robot the origin
//new y = R(1-cos(theta)). new x = Rsin(theta).
//new overall 