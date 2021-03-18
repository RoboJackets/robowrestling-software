#ifndef sensor_struct
#define sensor_struct

#include <vector>

struct EncoderBuffer
{
    std::vector<int> buffer;
} typedef EncoderBuffer;

struct ImuData 
{
    double x_accel_;
    double y_accel_;
    double z_gyro_;
} typedef ImuData;

struct LineBuffer
{
    std::vector<int> buffer;
} typedef LineBuffer;

struct DistanceBuffer 
{
    std::vector<double> buffer;
} typedef DistanceBuffer;

#endif