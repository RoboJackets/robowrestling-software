#ifndef abstract_distance_sensor_h
#define abstract_distance_sensor_h

#include "robot.h"

class AbstractDistanceSensor {
    public:
        int d_x_;
        int d_y_;
        int d_angle_;
        // Robot* robot_; // robot this sensor is on
    
    public: 
        int read() {
            return 0;
        }

        void setSensorPosition(int d_x, int d_y, int d_angle) {
            d_x_ = d_x;
            d_y_ = d_y;
            d_angle_ = d_angle;
        };
        
        // void setRobot(Robot* robot) {
        //     robot_ = robot;
        // }

        int getX() {return d_x_;};
        int getY() {return d_y_;};
        int getAngle() {return d_angle_;};
        // Robot* getRobot() {return robot_;};
};

#endif