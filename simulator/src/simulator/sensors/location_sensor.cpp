#include <simulator/sensors/distance_sensor_j.h> 

LocationSensor::LocationSensor(std::shared_ptr<Robot> robot, double d_x, double d_y) {
    robot_ = robot;
    _d_x = d_x;
    _d_y = d_y;
}

double LocactionSensor::read() {
    
}