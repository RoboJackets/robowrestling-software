#ifndef SLAMMY_WHAMMY_IMPROVED_H_
#define SLAMMY_WHAMMY_IMPROVED_H_

#include "Strategies/Strategy.hpp"

enum Direction { DLEFT, DRIGHT, DNONE };

class SlammyWhammy : public Strategy {
    private:
        enum Direction last_seen;
    public:
        SlammyWhammy();

        void make_decision(State* state);
};

#endif // SLAMMY_WHAMMY_IMPROVED_H_
