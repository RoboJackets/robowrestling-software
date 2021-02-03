#ifndef distance_sensor_h
#define distance_sensor_h

#include <simulator/robot.h>
#include <simulator/abstract_distance_sensor.h>
#include <math.h>

class DistanceSensor : public AbstractDistanceSensor {
    public: 
        DistanceSensor();
        DistanceSensor(std::shared_ptr<Robot> robot, double d_x, double d_y, double d_angle, double cone_angle, double cone_length);
        /*
        returns distance from a specified Robot
        */
        double read(std::shared_ptr<Robot> target);
        
};

#endif