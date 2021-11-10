#ifndef distance_sensor_j_h
#define distance_sensor_j_h

#include <simulator/sensors/abstract_distance_sensor_j.h>
#include <math.h>

#define pdd std::pair<double, double> 

class DistanceSensorJ : public AbstractDistanceSensorJ {
    public: 
        DistanceSensorJ(std::shared_ptr<Robot> robot, double sens_x, double sens_y, double sens_angle, double cone_angle, double cone_length);
        double read(std::shared_ptr<Robot> target);
        double get_distance(pdd corner);
};

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D);

#endif