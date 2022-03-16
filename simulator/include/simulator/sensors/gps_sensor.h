#ifndef gps_sensor_h
#define gps_sensor_h

#include <simulator/sensors/abstract_gps_sensor.h>
#include <math.h>

#define pdd std::pair<double, double> 

class GPSSensor : public AbstractGPSSensor {
    public: 
        AbstractGPSSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y, double sens_angle, double cone_angle, double cone_length);
        double read(std::shared_ptr<Robot> target);
        double get_distance(pdd corner);
};

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D);

#endif