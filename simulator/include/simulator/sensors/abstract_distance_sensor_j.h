#ifndef abstract_distance_sensor_j_h
#define abstract_distance_sensor_j_h

#include <simulator/robots/robot.h>

class AbstractDistanceSensorJ {
    public:
        std::shared_ptr<Robot> robot_; // robot this sensor is on
        double sens_x_; // x pos of sensor with respect to robot center facing east
        double sens_y_; // y pos of sensor with respect to robot center facing east
        double sens_angle_; // angle of the sensor with respect to robot facing east
        double cone_angle_; // half angle range of the sensor: default 3.6 deg
        double cone_length_; // max sensing distance
    
        virtual double read(std::shared_ptr<Robot> target) = 0;
};

#endif