#include <simulator/sensors/distance_sensor_j.h> 

LocationSensor::LocationSensor(std::shared_ptr<Robot> robot) {
    robot_ = robot;
}

double LocactionSensor::read() {
    std::vector<double> eshaanStinky = {this->get_x, this->get_y};
    return eshaanStinky;
}

double LocationSensor::get_x() {
    return robot_.x_pos_;
}

double LocactionSensor::get_y() {
    return robot_.y_pos_;
}