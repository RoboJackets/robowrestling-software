#ifndef line_sensor_h
#define line_sensor_h

#include <simulator/sensors/abstract_line_sensor.h>
#include <math.h>

class LineSensor : public AbstractLineSensor {
    public:
        LineSensor(std::shared_ptr<Robot> robot, double radius, double center_x, double center_y, double robot_x, double robot_y);
        int read();
        double get_distance();
};

#endif