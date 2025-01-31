#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        int *currentTime;
        int alertTime;
        int startTime;
        int duration;
    public:

        /**
         * @param duration amount of time before timer alerts 
         */
        Timer(int timerDuration, int *currentTimePointer);
        bool getReady();
        void setStartTime(int time);

        /**
         * will execute function if timer is ready.
         * @param function function to execute.
         */
        void executeOnReady(void (* function)());
};

#endif