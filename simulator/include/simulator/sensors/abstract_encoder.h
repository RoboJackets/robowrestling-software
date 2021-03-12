#ifndef abstract_encoder_h
#define abstract_encoder_h

#include <simulator/robots/robot.h>

class AbstractEncoder {
    public:
        std::shared_ptr<Robot> robot_; // robot this sensor is on
        int tick_total_; // the number of ticks per revolution of the motor
        double prev_wheel_velocity_; //previous velocity for determing accel

        virtual int get_tick(double duration) = 0; // returns ticks revolved through
        virtual int read(double duration) = 0; // polls the encoder
};

#endif