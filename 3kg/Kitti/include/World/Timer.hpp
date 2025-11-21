#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
    private:
        unsigned long start_time;
        unsigned long duration;
        unsigned long global_time;
        bool runningProcess;
    public:
        Timer(unsigned long initial_time);
        void begin();
        void startTimer(unsigned long duration);
        void updateTime();
        bool getRunningProcess();
        int getDuration();
};

#endif // TIMER_HPP