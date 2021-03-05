#ifndef basicrobot_handler_h
#define basicrobot_handler_h

#include <simulator/sensors/abstract_sensor_handler.h>

#include <simulator/sensors/distance_sensor.h>
#include <simulator/sensors/imu.h>

class BasicRobotHandler : public AbstractSensorHandler {
    public:
        BasicRobotHandler(std::shared_ptr<Robot> r);

        std::vector<double> read(double duration);
        std::vector<double> read(double duration, std::shared_ptr<Robot> target);

        std::unique_ptr<DistanceSensor> dist_;
        std::unique_ptr<IMU> imu_;
};

#endif