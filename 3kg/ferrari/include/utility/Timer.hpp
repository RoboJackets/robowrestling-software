#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        int *currentTime;
        int alertTime;
    public:

        /**
         * @param duration amount of time before timer alerts 
         */
        Timer(int duration, int *currentTimePointer);
        bool getReady();

        /**
         * will execute function if timer is ready.
         * @param function function to execute.
         */
        void executeOnReady(void (* function)());
};

#endif