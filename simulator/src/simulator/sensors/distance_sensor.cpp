#include "distance_sensor.h"
#include <math.h>
#include <iostream>


DistanceSensor::DistanceSensor(Robot* robot, double x, double y, double angle, double cone_angle, double cone_length) {
    setRobot(robot);
    setSensorPosition(x, y, angle);
    setConeData(cone_angle, cone_length);
};


double DistanceSensor::read(Robot* target) {
    double dx = _robot->x_pos + _d_x - target->x_pos;
    double dy = _robot->y_pos + _d_y - target->y_pos;
    double d_angle = _robot->angle + _d_angle - target->angle;

    std::cout << dx << " " << dy << std::endl;
    
    if (abs(atan(dy/dx)) >= _cone_angle) {
        return -1; // not found, target robot outside of cone
    }
    return sqrt(dx*dx + dy*dy);
};
