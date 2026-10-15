#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#include <Arduino.h>

class AutoTimer {
    private:
        bool started;
        int time;
        int startTime;
        int timerlength;
    public:
        AutoTimer(int _timerlength);
        bool getReady();
        void resetTimer();
};

#endif