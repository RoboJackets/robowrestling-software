#ifndef brodyrobot_handler_h
#define brodyrobot_handeler_h

#include <simulator/sensors/abstract_sensor_handler.h>

#include <simulator/sensors/distance_sensor_j.h>
#include <simulator/sensors/imu.h>
#include <simulator/sensors/line_sensor.h>
#include <simulator/sensors/encoder.h>
#include <simulator/sensor/location_sensor.h>

class BrodyRobotHandler: public AbstractSensorHandler {
    public:
        BrodyRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o);

        SensorData read(double duration);
        std::vector<std::shared_ptr<DistanceSensorJ>> dist_;
        std::shared_ptr<IMU> imu_;
        std::vector<std::shared_ptr<LineSensor>> line_;
        std::vector<std::shared_ptr<Encoder>> enc_;
        std::vector<std::shared_ptr<LocactionSensor> loc_;

};

#endif