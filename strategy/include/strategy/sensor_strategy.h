#include <strategy/strategy.h>
#include <simulator/sensors/encoder.h>
#include <simulator/sensors/imu.h>
#include <simulator/sensors/line_sensor.h>

class SensorStrategy: public Strategy {
    public:
        SensorStrategy();
        std::vector<int> next_action(std::vector<double> inputs);
        int state_;
};