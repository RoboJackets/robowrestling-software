#ifndef TIMER_H
#define TIMER_H

class timer {
    private:
        int match_start;
        int action_start;
        int action_length;
        int current_time;
        bool timer_set;
    public:
        timer(int intial_time);
        
        void update_time(int new_time);
        bool check_action_time();
        int check_match_time();
        void set_action_timer(int length);
        int get_action_start();
        int get_current_time();
};

#endif