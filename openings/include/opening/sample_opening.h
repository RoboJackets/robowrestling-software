#ifndef SAMPLE_OPENING_H
#define SAMPLE_OPENING_H
#include <opening/opening.h>

class SampleOpening: public Opening {
    public:
        int end;
        bool stop;
        SampleOpening();
        std::vector<int> execute(SensorData input);
};

#endif