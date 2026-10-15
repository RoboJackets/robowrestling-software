#ifndef TIMER_H
#define TIMER_H

// TODO: make timer have a parameter function call that gets called when ready as oppose to current implementation

class Timer {
    private:
        int currentTime;
        int previousTime;
        int timeInterval;
    public:
        bool getReady();
        void setTimeInterval(int time);
        void setCurrentTime(int time);
        void setPreviousTime(int time);
};

#endif