#ifndef sensor_struct
#define sensor_struct

#include <vector>

struct SensorData
{
    //all data is placed in vectors from left to right
    std::vector<int> encoder_buffer_;

    double x_accel_;
    double y_accel_;
    double z_gyro_;

    std::vector<int> line_buffer_;

    std::vector<double> dist_buffer_;
} typedef SensorData;

#endif