#include <simulator/distance_sensor.h>

#include <iostream>
#include <vector>
#include <algorithm>

DistanceSensor::DistanceSensor(std::shared_ptr<Robot> robot, double x, double y, double angle, double cone_angle, double cone_length) {
    setRobot(robot);
    setSensorPosition(x, y, angle);
    setConeData(cone_angle, cone_length);
};

DistanceSensor::DistanceSensor(){};

double DistanceSensor::read(std::shared_ptr<Robot> target) {
    double width = target->width_;
    double length = target->length_;

    std::vector<double> center = {target->x_pos_, target->y_pos_};
    
    std::vector<double> w_vec = {cos(_d_angle)*width/2, sin(_d_angle)*width/2};
    std::vector<double> l_vec = {-sin(_d_angle)*length/2, cos(_d_angle)*length/2};
    
    std::vector<std::vector<double>> corners = {
        {center[0] + w_vec[0] + l_vec[0], center[1] + w_vec[1] + l_vec[1]},
        {center[0] - w_vec[0] + l_vec[0], center[1] - w_vec[1] + l_vec[1]}, 
        {center[0] + w_vec[0] - l_vec[0], center[1] + w_vec[1] - l_vec[1]}, 
        {center[0] - w_vec[0] - l_vec[0], center[1] - w_vec[1] - l_vec[1]}
    };

    if (_d_angle == target -> angle_ || fmod(abs(_d_angle - target->angle_), M_PI/2) < 0.1) {
        // sensor perpendicular or parallel to the target, shortest distance will be to an edge not a corner
        double m = (corners[0][0]-corners[1][0])/(corners[0][1]-corners[1][1]);
        double c = -m*corners[0][0];
        double dist1 = abs(m*corners[0][0]-corners[0][1]+c)/sqrt(m*m + 1);

        m = (corners[1][0]-corners[2][0])/(corners[1][1]-corners[2][1]);
        c = -m*corners[1][0];
        double dist2 = abs(m*corners[0][0]-corners[0][1]+c)/sqrt(m*m + 1);
        return dist1 < dist2 ? dist1 : dist2;
    } 

    double sensor_x = _d_x + _robot->x_pos_;
    double sensor_y = _d_y + _robot->y_pos_;

    std::vector<double> corner_dists = {
        pow(corners[0][0]-sensor_x, 2.0) + pow(corners[0][1]-sensor_y, 2.0),
        pow(corners[1][0]-sensor_x, 2.0) + pow(corners[1][1]-sensor_y, 2.0),
        pow(corners[2][0]-sensor_x, 2.0) + pow(corners[2][1]-sensor_y, 2.0),
        pow(corners[3][0]-sensor_x, 2.0) + pow(corners[3][1]-sensor_y, 2.0)
    };
    
    double min_dist = *std::min_element(std::begin(corner_dists), std::end(corner_dists));
    return sqrt(min_dist);
};
