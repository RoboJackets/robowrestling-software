#ifndef abstract_distance_sensor_h
#define abstract_distance_sensor_h

#include <simulator/robots/robot.h>

class AbstractDistanceSensor {
    public:
        double _d_x;
        double _d_y;
        double _d_angle;
        std::shared_ptr<Robot> _robot; // robot this sensor is on
        double _cone_angle;
        double _cone_length;
    
        double read(std::shared_ptr<Robot> target);

        void setSensorPosition(double d_x, double d_y, double d_angle) {
            _d_x = d_x;
            _d_y = d_y;
            _d_angle = d_angle;
        };

        void setConeData(double cone_angle, double cone_length) {
            _cone_angle = cone_angle;
            _cone_length = cone_length;
        }
        
        void setRobot(std::shared_ptr<Robot> robot) {
            _robot = robot;
        }

        double getX() {return _d_x;};
        double getY() {return _d_y;};
        double getAngle() {return _d_angle;};
        std::shared_ptr<Robot> getRobot() {return _robot;};
};

#endif