#ifndef TIMER_H
#define TIMER_H

class timer {
    private:
        unsigned long match_start;
        unsigned long action_start;
        unsigned long action_length;
        unsigned long current_time;
        bool timer_state;
    public:
        timer(unsigned long intial_time);
        
        void update_time(unsigned long new_time);
        bool check_action_time();
        unsigned long check_match_time();
        void set_action_timer(unsigned long length);
        unsigned long get_action_start();
        unsigned long get_current_time();
        bool get_timer_state();
        void set_stopwatch();
        unsigned long check_stopwatch();
};

#endif