#ifndef abstract_imu_h
#define abstract_imu_h

#include <memory>
#include <simulator/robot.h>

class AbstractIMU {
    public:
        std::shared_ptr<Robot> robot_; // robot this sensor is on
        double prev_left_wheel_velocity_; //previous velocities for determing accel
        double prev_right_wheel_velocity_;
        double prev_angle_; //previous robot angle for determining rotation

        virtual double get_x_accel(double duration) = 0;
        virtual double get_y_accel(double duration) = 0;
        virtual double get_z_gyro(double duration) = 0;
};

#endif