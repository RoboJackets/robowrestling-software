#ifndef abstract_gps_sensor_h
#define abstract_gps_sensor_h

#include <simulator/robots/robot.h>

class AbstractGPSSensor {
    public:
        std::shared_ptr<Robot> robot_; // robot this sensor is on
         double sens_x_; // x pos of sensor with respect to robot center facing east in cm aka pixels
         double sens_y_; // y pos of sensor with respect to robot center facing east in cm aka pixels
//         double sens_angle_; // angle of the sensor with respect to robot facing east in radians
//         double cone_angle_; // half angle range of the sensor: default 3.6 deg (whatever that is in radians)
//         double cone_length_; // max sensing distance in cm aka pixels
    
//         virtual double read(std::shared_ptr<Robot> target) = 0;
// };
};

#endif