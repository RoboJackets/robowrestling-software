#ifndef location_sensor_h
#define location_sensor_h

#include <simulator/sensors/abstract_location_sensor.h>

class LocationSensor : public AbstractLocaitonSensor {
    public:
        LocationSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y);
        std::vector<double> read();
        double get_x();
        double get_y();
};

#endif