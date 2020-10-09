#ifndef distance_sensor_h
#define distance_sensor_h

#include "robot.h"
#include "abstract_distance_sensor.h"
#include <math.h>

class DistanceSensor : public AbstractDistanceSensor {
    public: 
        DistanceSensor(Robot* robot, double d_x, double d_y, double d_angle, double cone_angle, double cone_length);
        /*
        returns distance from a specified Robot
        */
        double read(Robot* target);
};

#endif