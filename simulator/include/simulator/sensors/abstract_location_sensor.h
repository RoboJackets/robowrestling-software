#ifndef abstract_location_sensor_h
#define abstract_location_sensor_h

#include <simulator/robots/robot.h>

class AbstractLocaitonSensor {
    public:
        std::shared_ptr<Robot> robot_;
        double sens_x_;
        double sens_y_;
        virtual std::vector<double> read() = 0;
        double get_x();
        double get_y();
};

#endif