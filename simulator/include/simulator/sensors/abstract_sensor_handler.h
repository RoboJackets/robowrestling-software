#ifndef abstract_sensor_handler_h
#define abstract_sensor_handler_h

#include <simulator/robots/robot.h>
#include <sensor_struct.h>

class AbstractSensorHandler {
    public:
        virtual SensorData read(double duration) = 0;
        std::shared_ptr<Robot> robot_;
        std::shared_ptr<Robot> opponent_;
};

#endif