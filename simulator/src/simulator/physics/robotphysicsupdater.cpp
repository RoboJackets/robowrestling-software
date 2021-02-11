#include <simulator/physics/robotphysicsupdater.h>
#include <iostream>

RobotPhysicsUpdater::RobotPhysicsUpdater() {

}

void RobotPhysicsUpdater::update(std::shared_ptr<Robot> r1, std::vector<int> r1_update, std::shared_ptr<Robot> r2, std::vector<int> r2_update, double duration) {
	this->move_robot(r1, r1_update[0], r1_update[1], duration);
	this->move_robot(r2, r2_update[0], r2_update[1], duration);
	std::cout << this->check_collision(r1, r2) << std::endl;
	
}

bool RobotPhysicsUpdater::check_collision(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2) {

	auto r1_corners = r1->corners(); //std vector of std pairs representing the 4 corners of the robot
	auto r2_corners = r2->corners(); 
	double axis1_slope = (r1_corners[0].second - r1_corners[1].second) / (r1_corners[0].first - r1_corners[1].first); //https://gamedev.stackexchange.com/questions/25397/obb-vs-obb-collision-detection
	double axis1_offset = -1*axis1_slope*r1_corners[0].first + r1_corners[0].second;
	bool overlap1 = false;
	double axis2_slope = (r1_corners[1].second - r1_corners[2].second) / (r1_corners[1].first - r1_corners[2].first);
	double axis2_offset = -1*axis2_slope*r1_corners[1].first + r1_corners[1].second;
	bool overlap2 = false;
	if (axis1_slope == 0) {
		for (int i = 0; i < 4; i++) {
			if (r1_corners[0].first > r1_corners[1].first) {
				if (r2_corners[i].first <= r1_corners[0].first && r2_corners[i].first >= r1_corners[1].first) {
					overlap1 = true;
				}
			} else {
				if (r2_corners[i].first >= r1_corners[0].first && r2_corners[i].first <= r1_corners[1].first) {
					overlap1 = true;
				}
			}
			if (r1_corners[1].second > r1_corners[2].second) {
				if (r2_corners[i].second <= r1_corners[1].second && r2_corners[i].second >= r1_corners[2].second) {
					overlap2 = true;
				}
			} else {
				if (r2_corners[i].second >= r1_corners[1].second && r2_corners[i].second <= r1_corners[2].second) {
					overlap2 = true;
				}
			}
		}
	} else if (axis2_slope == 0) {
		for (int i = 0; i < 4; i++) {
			if (r1_corners[0].second > r1_corners[1].second) {
				if (r2_corners[i].second <= r1_corners[0].second && r2_corners[i].second >= r1_corners[1].second) {
					overlap1 = true;
				}
			} else {
				if (r2_corners[i].second >= r1_corners[0].second && r2_corners[i].second <= r1_corners[1].second) {
					overlap1 = true;
				}
			}
			if (r1_corners[1].first > r1_corners[2].first) {
				if (r2_corners[i].first <= r1_corners[1].first && r2_corners[i].first >= r1_corners[2].first) {
					overlap2 = true;
				}
			} else {
				if (r2_corners[i].first >= r1_corners[1].first && r2_corners[i].first <= r1_corners[2].first) {
					overlap2 = true;
				}
			}
		}
	} else {
		for (int i = 0; i < 4; i++) {
			double offset = ((1/axis1_slope) * r2_corners[i].first) + r2_corners[i].second;
			double projection_x = (offset-axis1_offset)/(1/axis1_slope + axis1_slope);
			double projection_y = axis1_offset + axis1_slope*projection_x;
			if (r1_corners[0].second > r1_corners[1].second) {
				if (projection_y <= r1_corners[0].second && projection_y >= r1_corners[1].second) {
					overlap1 = true;
				}
			} else if (projection_y >= r1_corners[0].second && projection_y <= r1_corners[1].second) {
				overlap1 = true;
			}
		}
		for (int i = 0; i < 4; i++) {
			double offset = ((1/axis2_slope) * r2_corners[i].first) + r2_corners[i].second;
			double projection_x = (offset-axis2_offset)/(1/axis2_slope + axis2_slope);
			double projection_y = axis2_offset + axis2_slope*projection_x;
			if (r1_corners[1].second > r1_corners[2].second) {
				if (projection_y <= r1_corners[1].second && projection_y >= r1_corners[2].second) {
					overlap2 = true;
				}
			} else if (projection_y >= r1_corners[1].second && projection_y <= r1_corners[2].second) {
				overlap2 = true;
			}
		}
	}
	if (overlap1 && overlap2) {
		return true;
	} else {
		return false;
	}
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