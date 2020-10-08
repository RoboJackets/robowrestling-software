#ifndef abstract_distance_sensor_h
#define abstract_distance_sensor_h

#include "robot.h"

class AbstractDistanceSensor {
    public:
        double d_x_;
        double d_y_;
        double d_angle_;
        Robot* robot_; // robot this sensor is on
        AbstractDistanceSensor() {};
    
    public: 
        double read(Robot* target) {
            return 0;
        }

        void setSensorPosition(double d_x, double d_y, double d_angle) {
            d_x_ = d_x;
            d_y_ = d_y;
            d_angle_ = d_angle;
        };
        
        void setRobot(Robot* robot) {
            robot_ = robot;
        }

        double getX() {return d_x_;};
        double getY() {return d_y_;};
        double getAngle() {return d_angle_;};
        Robot* getRobot() {return robot_;};
};

#endif