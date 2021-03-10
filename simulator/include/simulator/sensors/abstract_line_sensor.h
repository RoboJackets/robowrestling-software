#ifndef abstract_line_sensor_h
#define abstract_line_sensor_h

#include <simulator/robots/robot.h>

class AbstractLineSensor {
    public:
        std::shared_ptr<Robot> robot_; // robot this sensor is on
        double radius_; // radius of the dohyo
        double center_x_; // x center of the dohyo
        double center_y_; // y center of the dohyo
        double line_x_; // x pos of sensor with respect to robot center facing east
        double line_y_; // y pos of sensor with respect to robot center facing east

        virtual int read() = 0; //255 is active, 0 is inactive
        virtual double get_distance() = 0;
};

#endif