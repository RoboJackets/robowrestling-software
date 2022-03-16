#ifndef abstract_location_sensor_h
#define abstract_location_sensor_h

#include <simulator/robots/robot.h>

class AbstractLocaitonSensor {
    public:
        std::shared_ptr<Robot> _robot;
        double _d_x;
        double _d_y;
        virtual double read() = 0;
}

#endif