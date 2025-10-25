#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
    private:
        bool activated;
        unsigned long currentTime;
        unsigned long targetTime;
        unsigned long duration;
    public:
        Timer(unsigned long _duration, bool startActivated = false);
        bool isReady();
        void resetTimer();
};

#endif