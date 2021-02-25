#ifndef abstract_sensor_handler_h
#define abstract_sensor_handler_h

#include <simulator/robot.h>

class AbstractSensorHandler {
    public:
        virtual std::vector<double> read(double duration) = 0;
        std::shared_ptr<Robot> robot_;
};

#endif