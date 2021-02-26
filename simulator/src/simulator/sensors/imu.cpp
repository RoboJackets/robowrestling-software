#include <simulator/sensors/imu.h>

IMU::IMU(std::shared_ptr<Robot> r) {
    robot_ = r;
    prev_left_wheel_velocity_ = r->left_wheel_velocity_;
    prev_right_wheel_velocity_ = r->right_wheel_velocity_;
    prev_angle_ = r->angle_;
}

std::vector<double> IMU::read(double duration) {
    std::vector<double> ret = {this->get_x_accel(duration), this->get_y_accel(duration), this->get_z_gyro(duration)};
    prev_left_wheel_velocity_ = robot_->left_wheel_velocity_;
    prev_right_wheel_velocity_ = robot_->right_wheel_velocity_;
    prev_angle_ = robot_->angle_;
    return ret;
}

double IMU::get_x_accel(double duration) {
    auto ret = (((robot_->left_wheel_velocity_ + robot_->right_wheel_velocity_) / 2) * cos(robot_->angle_)) - (((prev_left_wheel_velocity_ + prev_right_wheel_velocity_) / 2) * cos(prev_angle_)) / duration;
    return ret;
}

double IMU::get_y_accel(double duration) {
    auto ret = (((robot_->left_wheel_velocity_ + robot_->right_wheel_velocity_) / 2) * sin(robot_->angle_)) - (((prev_left_wheel_velocity_ + prev_right_wheel_velocity_) / 2) * sin(prev_angle_)) / duration;
    return ret;
}

double IMU::get_z_gyro(double duration) {
    auto ret = (robot_->angle_ - prev_angle_) / duration;
    return ret;
}