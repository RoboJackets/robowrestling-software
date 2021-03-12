#ifndef encoder_h
#define encoder_h

#include <simulator/sensors/abstract_encoder.h>
#include <cmath>

class Encoder : public AbstractEncoder {
    public:
        Encoder(std::shared_ptr<Robot> robot, int tick_total, bool motor_side); // motor_side = true:left, false:right
        bool motor_side_;

        int get_tick(double duration);
        int read(double duration);
};
#endif