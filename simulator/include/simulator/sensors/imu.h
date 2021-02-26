#ifndef imu_h
#define imu_h

#include <simulator/sensors/abstract_imu.h>

class IMU : public AbstractIMU {
    public:
        IMU(std::shared_ptr<Robot> r);

        double get_x_accel(double duration);
        double get_y_accel(double duration);
        double get_z_gyro(double duration);
        std::vector<double> read(double duration);
};
#endif