#ifndef ANTI_AIM_H
#define ANTI_AIM_H
#include <strategy/strategy.h> 

// based on the simulator, this strategy works 50% of the time
// basically we want the other robot to just phase right through
class AntiAim: public Strategy {
    public:
        AntiAim();
        std::vector<int> next_action(SensorData input);

        enum State {
            STOP,
            SPIN
        };
        State state;
        State update_state(SensorData input);
};

#endif
