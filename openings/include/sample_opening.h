#include <strategy/strategy.h>

class SampleOpening: public Strategy {
    public:
        SampleOpening();
        std::vector<int> next_action(SensorData input);
};