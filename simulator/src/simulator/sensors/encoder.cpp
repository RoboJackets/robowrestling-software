#include <simulator/sensors/encoder.h>

Encoder::Encoder(std::shared_ptr<Robot> robot, int tick_total, bool motor_side) {
    robot_ = robot;
    tick_total_ = tick_total;
    motor_side_ = motor_side;
    if (motor_side_) {
        prev_wheel_velocity_ = robot->left_wheel_velocity_;
    } else {
        prev_wheel_velocity_ = robot->right_wheel_velocity_;
    }
}

int Encoder::read(double duration) {
    int ret = this->get_tick(duration);
    if (motor_side_) {
        prev_wheel_velocity_ = robot_->left_wheel_velocity_;
    } else {
        prev_wheel_velocity_ = robot_->right_wheel_velocity_;
    }
    return ret;
}

int Encoder::get_tick(double duration) {
    double rad;
    if (motor_side_) {
        rad = (duration * (prev_wheel_velocity_ + robot_->left_wheel_velocity_) / 2);
    } else {
        rad = (duration * (prev_wheel_velocity_ + robot_->right_wheel_velocity_) / 2);
    }
    int ret = (int) (tick_total_ * rad / (2 * M_PI));
    return ret;
}
