#ifndef basicrobot_handler_h
#define basicrobot_handler_h

#include <simulator/sensors/abstract_sensor_handler.h>

#include <simulator/sensors/distance_sensor_j.h>
#include <simulator/sensors/imu.h>
#include <simulator/sensors/line_sensor.h>
#include <simulator/sensors/encoder.h>

class BasicRobotHandler : public AbstractSensorHandler {
    public:
        BasicRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o);

        SensorData read(double duration);

        std::vector<std::shared_ptr<DistanceSensorJ>> dist_;
        std::shared_ptr<IMU> imu_;
        std::vector<std::shared_ptr<LineSensor>> line_;
        std::vector<std::shared_ptr<Encoder>> enc_;

};

#endif