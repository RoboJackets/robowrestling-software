#ifndef gps_sensor_h
#define gps_sensor_h

#include <simulator/sensors/abstract_gps_sensor.h>
#include <math.h>

#define pdd std::pair<double, double> 

class GPSSensor : public AbstractGPSSensor {
    public: 
        GPSSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y);
        // double read(std::shared_ptr<Robot> robot); //read it's own data
        // double get_distance(pdd corner); // not sure if we really need to get distance, we need to get values 
        double get_y_pos();
        double get_x_pos();
};

#endif