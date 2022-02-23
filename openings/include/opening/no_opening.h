#ifndef NO_OPENING_H
#define NO_OPENING_H
#include <opening/opening.h>

#include <chrono>
using namespace std::literals;

class NoOpening: public Opening {
    public:
        NoOpening();
        std::vector<int> execute(SensorData input);
        bool done = false;
};

#endif