#ifndef ROBOWRESTLING_SOFTWARE_SLAMMYWHAMMY_H
#define ROBOWRESTLING_SOFTWARE_SLAMMYWHAMMY_H
#include <strategy/strategy.h>

class SlammyWhammy: public Strategy {
    public:
        SlammyWhammy();
        std::vector<int> next_action(SensorData input);
        int state_;
};

#endif //ROBOWRESTLING_SOFTWARE_SLAMMYWHAMMY_H
