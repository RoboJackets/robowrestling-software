/*
* From Celebi program implementations
*/
#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        unsigned long match_start;
        unsigned long action_start;
        unsigned long action_length;
        unsigned long current_time;
        bool timer_state;
    public:
        Timer(unsigned long intial_time);
        
        void update_time(unsigned long new_time);
        bool check_action_time();
        unsigned long check_match_time();
        void set_action_timer(unsigned long length);
        unsigned long get_action_start();
        unsigned long get_current_time();
        bool get_timer_state();
};

#endif