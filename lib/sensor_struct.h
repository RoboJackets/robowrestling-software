#ifndef sensor_struct
#define sensor_struct

#include <vector>

struct encoderBuffer
{
    std::vector<int> buffer;
} typedef encoderBuffer;

struct imuData 
{
    double x_accel_;
    double y_accel_;
    double z_gyro_;
} typedef imuData;

struct lineBuffer
{
    std::vector<int> buffer;
} typedef lineBuffer;

struct distanceBuffer 
{
    std::vector<double> buffer;
} typedef distanceBuffer;

#endif