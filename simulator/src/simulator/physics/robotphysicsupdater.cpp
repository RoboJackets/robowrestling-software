#include <simulator/physics/robotphysicsupdater.h>
#include <iostream>

RobotPhysicsUpdater::RobotPhysicsUpdater() {

}

void RobotPhysicsUpdater::move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration) {
	//calculate how fast the right wheel moves
	// std::cout << r->angle << std::endl;
	double desired_right_velocity = (right_wheel/100.0)*r->max_wheel_velocity_;
	double right_new_velocity = desired_right_velocity;
	if (r->right_wheel_velocity_ < desired_right_velocity) {
		double right_velocity_increase = duration * r->wheel_acceleration_;
		right_new_velocity = r->right_wheel_velocity_ + right_velocity_increase;
		if (right_new_velocity > desired_right_velocity) {
			right_new_velocity = desired_right_velocity;
		}
	} else if (r->right_wheel_velocity_ > desired_right_velocity) {
		double right_velocity_decrease = duration * r->wheel_acceleration_;
		right_new_velocity = r->right_wheel_velocity_ - right_velocity_decrease;
		if (right_new_velocity < desired_right_velocity) {
			right_new_velocity = desired_right_velocity;
		}
	}
	double average_right_velocity = (right_new_velocity + r->right_wheel_velocity_) / 2;
	r->right_wheel_velocity_ = right_new_velocity;
	//calculate how fast the left wheel moves
	double desired_left_velocity = (left_wheel/100.0)*r->max_wheel_velocity_;
	double left_new_velocity = desired_left_velocity;
	if (r->left_wheel_velocity_ < desired_left_velocity) {
		double left_velocity_increase = duration * r->wheel_acceleration_;
		left_new_velocity = r->left_wheel_velocity_ + left_velocity_increase;
		if (left_new_velocity > desired_left_velocity) {
			left_new_velocity = desired_left_velocity;
		}
	} else if (r->left_wheel_velocity_ > desired_left_velocity) {
		double left_velocity_decrease = duration * r->wheel_acceleration_;
		left_new_velocity = r->left_wheel_velocity_ - left_velocity_decrease;
		if (left_new_velocity < desired_left_velocity) {
			left_new_velocity = desired_left_velocity;
		}
	}
	double average_left_velocity = (left_new_velocity + r->left_wheel_velocity_) / 2;
	r->left_wheel_velocity_ = left_new_velocity;
	// std::cout << average_left_velocity << ", " << average_right_velocity << std::endl;
	if (average_left_velocity == average_right_velocity) {
		double linear_velocity = average_right_velocity * r->wheel_radius_;
		double distance_traveled = linear_velocity * duration;
		double x_change = distance_traveled * cos(r->angle_);
		double y_change = distance_traveled * sin(r->angle_);
		r->x_pos_ += x_change;
		r->y_pos_ += y_change;
	} else if (average_left_velocity == -average_right_velocity) {
		double rotational_velocity = (average_right_velocity - average_left_velocity)/(r->width_);
		double angle_change = rotational_velocity * duration;
		r->angle_ += angle_change;
	} else {
		// std::cout << average_left_velocity << std::endl;
		double rotational_velocity = (average_right_velocity - average_left_velocity)/(r->width_);
		// std::cout << average_right_velocity - average_left_velocity << std::endl;
		double curvature_radius = 0;
		if (average_left_velocity == 0 || average_right_velocity == 0) {
			curvature_radius = r->width_/2;
		} else {
			curvature_radius = ((average_left_velocity + average_right_velocity)/(average_right_velocity - average_left_velocity))/2;
		}
		// std::cout << curvature_radius << std::endl;
		double angle_change = rotational_velocity * duration;
		// std::cout << angle_change << std::endl;
		double icc_x = r->x_pos_ - curvature_radius * sin(r->angle_);
		double icc_y = r->y_pos_ + curvature_radius * cos(r->angle_);
		double new_x = ((r->x_pos_ - icc_x) * cos(angle_change)) + ((r->y_pos_ - icc_y) * -sin(angle_change)) + icc_x;
		double new_y = ((r->x_pos_ - icc_x) * sin(angle_change)) + ((r->y_pos_ - icc_y) * cos(angle_change)) + icc_y;
		r->x_pos_ = new_x;
		r->y_pos_ = new_y;
		r->angle_ += angle_change;
	}
}
//Kinematics brought to you by http://www.cs.columbia.edu/~allen/F15/NOTES/icckinematics.pdf