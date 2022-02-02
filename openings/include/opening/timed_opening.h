#ifndef TIMED_OPENING_H
#define TIMED_OPENING_H
#include <opening/opening.h>

#include <chrono>
using namespace std::literals;

class TimedOpening: public Opening {
    public:
        std::chrono::time_point<std::chrono::system_clock> start_time;
        std::chrono::seconds time_limit{1};
        TimedOpening();
        std::vector<int> execute(SensorData input);
        bool done = false;
};

#endif