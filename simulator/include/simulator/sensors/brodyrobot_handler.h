#ifndef brodyrobot_handler_h
#define brodyrobot_handler_h

#include <simulator/sensors/abstract_sensor_handler.h>

#include <simulator/sensors/distance_sensor_j.h>
#include <simulator/sensors/line_sensor.h>
#include <simulator/sensors/location_sensor.h>

class BrodyRobotHandler: public AbstractSensorHandler {
    public:
        BrodyRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o);

        SensorData read(double duration);
        std::vector<std::shared_ptr<DistanceSensorJ>> dist_;
        std::vector<std::shared_ptr<LineSensor>> line_;
        std::shared_ptr<LocationSensor> loc_;

};

#endif