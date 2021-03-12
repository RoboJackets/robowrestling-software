#include <simulator/sensors/line_sensor.h>

LineSensor::LineSensor(std::shared_ptr<Robot> robot, double radius, double center_x, double center_y, double line_x, double line_y) {
    robot_ = robot;
    radius_ = radius;
    center_x_ = center_x;
    center_y_ = center_y;
    line_x_ = line_x;
    line_y_ = line_y;
}

int LineSensor::read() {
    if (get_distance() >= radius_) {
        return 255;
    } else {
        return 0;
    }
}

double LineSensor::get_distance() {
    double dist_x = (cos(robot_->angle_) * line_x_ - sin(robot_->angle_) * line_y_) + robot_->x_pos_ - center_x_;
    double dist_y = (cos(robot_->angle_) * line_x_ + sin(robot_->angle_) * line_y_) + robot_->y_pos_ - center_y_;
    return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}