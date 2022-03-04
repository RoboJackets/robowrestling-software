#include <simulator/physics/robotphysicsupdater.h>
#include <iostream>

RobotPhysicsUpdater::RobotPhysicsUpdater() {

}

void RobotPhysicsUpdater::update(std::shared_ptr<Robot> r1, std::vector<int> r1_update, std::shared_ptr<Robot> r2, std::vector<int> r2_update, double duration) {
	this->move_robot(r1, r1_update[0], r1_update[1], duration);
	this->move_robot(r2, r2_update[0], r2_update[1], duration);
	if (this->check_collision(r1, r2)) {
		this->collision_handler(r1, r2);
	}	
}

bool RobotPhysicsUpdater::check_collision(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2) {
	auto r1_corners = r1->corners(); //std vector of std pairs representing the 4 corners of the robot
	auto r2_corners = r2->corners();

	std::vector<pdd> normal_axis;
	normal_axis.push_back(pdd(-(r1_corners[1].second - r1_corners[0].second), (r1_corners[1].first - r1_corners[0].first)));
	normal_axis.push_back(pdd(-(r1_corners[2].second - r1_corners[1].second), (r1_corners[2].first - r1_corners[1].first)));
	normal_axis.push_back(pdd(-(r2_corners[1].second - r2_corners[0].second), (r2_corners[1].first - r2_corners[0].first)));
	normal_axis.push_back(pdd(-(r2_corners[2].second - r2_corners[1].second), (r2_corners[2].first - r2_corners[1].first)));

	for (u_int8_t i = 0; i < normal_axis.size(); i++) {
		double r1_min_along, r1_max_along, r2_min_along, r2_max_along;
		sat_test(normal_axis[i], r1_corners, r1_min_along, r1_max_along);
		sat_test(normal_axis[i], r2_corners, r2_min_along, r2_max_along);
		if (!overlaps(r1_min_along, r1_max_along, r2_min_along, r2_max_along)) {
			return false;
		}
	}
	return true;
}

void RobotPhysicsUpdater::sat_test(pdd normal_axis, std::vector<pdd> corners, double& min_along, double& max_along) {
	min_along = INT16_MAX;
	max_along = INT16_MIN;
  	for (u_int8_t i = 0; i < corners.size(); i++ ) {
		double dotVal = dot_product(corners[i], normal_axis) ;
		if (dotVal < min_along) {
			min_along = dotVal;
		}
		if (dotVal > max_along) {
			max_along = dotVal;
		}
	}
}

double RobotPhysicsUpdater::dot_product(pdd first, pdd second) {
	return first.first * second.first + first.second * second.second;
}

bool RobotPhysicsUpdater::overlaps(double min_1, double max_1, double min_2, double max_2) {
  return is_between_ordered(min_2, min_1, max_1) || is_between_ordered(min_1, min_2, max_2) ;
}

bool RobotPhysicsUpdater::is_between_ordered(double val, double lower_bound, double upper_bound) {
  return lower_bound <= val && val <= upper_bound ;
}

void RobotPhysicsUpdater::collision_handler(std::shared_ptr<Robot> r1, std::shared_ptr<Robot> r2) {
	double r2_x_to_r1 = r2->x_pos_ - r1->x_pos_; //shift using r1 as the origin
	double r2_y_to_r1 = r2->y_pos_ - r1->y_pos_;
	double relative_x = r2_x_to_r1*cos(-1*r1->angle_) - r2_y_to_r1*sin(-1*r1->angle_); //rotate axis so r1 is origin
	double relative_y = r2_x_to_r1*sin(-1*r1->angle_) + r2_y_to_r1*cos(-1*r1->angle_);
	double angle_r1_to_r2 = atan2(relative_y, relative_x); //inverse tangent to get the angle of r2 relative to where r1 is pointing
	double r1_x_to_r2 = r1->x_pos_ - r2->x_pos_; //shift using r2 as the origin
	double r1_y_to_r2 = r1->y_pos_ - r2->y_pos_;
	relative_x = r1_x_to_r2*cos(-1*r2->angle_) - r1_y_to_r2*sin(-1*r2->angle_); //rotate axis so r2 is origin
	relative_y = r1_x_to_r2*sin(-1*r2->angle_) + r1_y_to_r2*cos(-1*r2->angle_);
	double angle_r2_to_r1 = atan2(relative_y, relative_x); //inverse tangent to get the angle of r1 relative to where r2 is pointing
	// std::cout << angle_r1_to_r2 << ", " << angle_r2_to_r1 << std::endl;

	if (angle_r1_to_r2 <= M_PI/4 && angle_r1_to_r2 >= -M_PI/4) { //r1 faces r2
		if (angle_r2_to_r1 <= M_PI/4 && angle_r2_to_r1 >= -M_PI/4) { //r2 faces r1 aka Head on collision
			// std::cout << "Head On" << std::endl;

			auto r1_avg_velocity = (r1->left_wheel_velocity_ + r1->right_wheel_velocity_) / 2.0;
			auto r2_avg_velocity = (r2->left_wheel_velocity_ + r2->right_wheel_velocity_) / 2.0;
			auto total_velocity = (r1_avg_velocity + r2_avg_velocity) * 0.75; //total velocity in the system

			if (angle_r1_to_r2 < 0.05 && angle_r1_to_r2 > -0.05) {
				r1->left_wheel_velocity_ -= total_velocity / 2.0; //inelastic collision everything moves as a group 
				r1->right_wheel_velocity_ -= total_velocity / 2.0;
			} else {
				r1->left_wheel_velocity_ -= total_velocity / 2.0;
				r1->right_wheel_velocity_ -= total_velocity / 2.0;
				r1->angle_ += angle_r1_to_r2 * (total_velocity / (r1->max_wheel_velocity_ * 1.25)); //adjusts the angle to face the robots together
			}
			if (angle_r2_to_r1 < 0.05 && angle_r2_to_r1 > -0.05) {
				r2->left_wheel_velocity_ -= total_velocity / 2.0;
				r2->right_wheel_velocity_ -= total_velocity / 2.0;
			} else {
				r2->left_wheel_velocity_ -= total_velocity / 2.0;
				r2->right_wheel_velocity_ -= total_velocity / 2.0;
				r2->angle_ += angle_r2_to_r1 * (total_velocity / (r2->max_wheel_velocity_ * 1.25));
			}

		} else { //r1 hits r2
			std::cout << "R1 hit R2" << std::endl;
			r2->x_pos_ += (r1->left_wheel_velocity_ + r1->right_wheel_velocity_)*cos(r1->angle_)*.01;
			r2->y_pos_ += (r1->left_wheel_velocity_ + r1->right_wheel_velocity_)*sin(r1->angle_)*.01;
		}
	} else if (angle_r2_to_r1 <= M_PI/4 && angle_r2_to_r1 >= -M_PI/4) { //r2 hits r1
		std::cout << "R2 hit R1" << std::endl;
		r1->x_pos_ += (r2->left_wheel_velocity_ + r2->right_wheel_velocity_)*cos(r2->angle_)*.01;
		r1->y_pos_ += (r2->left_wheel_velocity_ + r2->right_wheel_velocity_)*sin(r2->angle_)*.01;
	}
}

/**
 * @brief calculate how fast a wheel moves
 * 
 * @param wheel_ds the percentage the motor is powered at
 * @param current_vel current velocity for that side of the robot
 * @param robot the robot
 * @param duration simulator elapsed time
 * @return double -- the new velocity 
 */
double RobotPhysicsUpdater::compute_wheel_velocity(std::shared_ptr<Robot> robot, double wheel_ds, double current_vel, double duration) {
	double desired_velocity = (wheel_ds/100.0) * robot->max_wheel_velocity_;
	double new_velocity = desired_velocity; 
	if (current_vel < desired_velocity) {
		double velocity_increase = duration * robot->wheel_acceleration_ * (wheel_ds/100.0);
		new_velocity = current_vel + velocity_increase; 
		if (new_velocity > desired_velocity) {
			new_velocity = desired_velocity; 
		}
	} else if (current_vel > desired_velocity) {
		double velocity_decrease = duration * robot->wheel_acceleration_; 
		new_velocity = current_vel - velocity_decrease; 
		if (new_velocity < desired_velocity) {
			new_velocity = desired_velocity; 
		}
	}

	return new_velocity; 
}


void RobotPhysicsUpdater::move_robot(std::shared_ptr<Robot> r, double left_wheel, double right_wheel, double duration) {
	//calculate how fast the right wheel moves
	double right_new_velocity = compute_wheel_velocity(r, right_wheel, r->right_wheel_velocity_, duration);
	double average_right_velocity = (right_new_velocity + r->right_wheel_velocity_) / 2;
	r->right_wheel_velocity_ = right_new_velocity;
	
	//calculate how fast the left wheel moves
	double left_new_velocity = compute_wheel_velocity(r, left_wheel, r->left_wheel_velocity_, duration);
	double average_left_velocity = (left_new_velocity + r->left_wheel_velocity_) / 2;
	r->left_wheel_velocity_ = left_new_velocity;

	if (average_left_velocity == average_right_velocity) {
		double linear_velocity = average_right_velocity * r->wheel_radius_;
		double distance_traveled = linear_velocity * duration;
		double x_change = distance_traveled * cos(r->angle_);
		double y_change = distance_traveled * sin(r->angle_);
		r->x_pos_ += x_change;
		r->y_pos_ += y_change;
	} else if (average_left_velocity == -average_right_velocity) {
		double rotational_velocity = (average_left_velocity - average_right_velocity)/(r->width_) * r->wheel_radius_; 
		double angle_change = rotational_velocity * duration;
		r->angle_ += angle_change;
	} else {
		//Kinematics brought to you by http://www.cs.columbia.edu/~allen/F15/NOTES/icckinematics.pdf
		average_left_velocity = average_left_velocity * r->wheel_radius_;
		average_right_velocity = average_right_velocity * r->wheel_radius_;
		double rotational_velocity = (average_left_velocity - average_right_velocity)/(r->width_);
		double curvature_radius = 0;
		if (average_left_velocity == 0) {
			curvature_radius = -r->width_/2;
		} else if (average_right_velocity == 0) {
			curvature_radius = r->width_/2;
		} else {
			curvature_radius = r->width_*((average_left_velocity + average_right_velocity)/(average_left_velocity - average_right_velocity))/2;
		}
		double angle_change = rotational_velocity * duration;
		double icc_x = r->x_pos_ - curvature_radius * sin(r->angle_);
		double icc_y = r->y_pos_ + curvature_radius * cos(r->angle_);
		double new_x = ((r->x_pos_ - icc_x) * cos(angle_change)) + ((r->y_pos_ - icc_y) * -sin(angle_change)) + icc_x;
		double new_y = ((r->x_pos_ - icc_x) * sin(angle_change)) + ((r->y_pos_ - icc_y) * cos(angle_change)) + icc_y;
		r->x_pos_ = new_x;
		r->y_pos_ = new_y;
		r->angle_ += angle_change;
	}
}
