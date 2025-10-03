#ifndef TRACK_H_
#define TRACK_H_

#include "Strategies/Strategy.hpp"

class Track : public Strategy {
    private:
        int fwd_speed, turn_speed;
    public:
        Track(int fwd_speed, int turn_speed);
        void make_decision(State* state);
};


#endif // TRACK_H_
