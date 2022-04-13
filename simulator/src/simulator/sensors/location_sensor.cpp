#include <simulator/sensors/location_sensor.h> 

LocationSensor::LocationSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y) {
    robot_ = robot;
    sens_x_ = sens_x;
    sens_y_ = sens_y;
}

std::vector<double> LocationSensor::read() {
    std::vector<double> eshaanStinky = {this->get_x(), this->get_y()};
    return eshaanStinky;
}

double LocationSensor::get_x() {
    return robot_->x_pos_;
}

double LocationSensor::get_y() {
    return robot_->y_pos_;
}