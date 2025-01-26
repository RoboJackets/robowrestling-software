#ifndef SLAMMY_WHAMMY_IMPROVED_H_
#define SLAMMY_WHAMMY_IMPROVED_H_

#include "Actions/Action.hpp"

enum Direction { LEFT, RIGHT, NONE };

class SlammyWhammy : public Action {
    private:
        enum Direction last_seen;
    public:
        SlammyWhammy();

        virtual void make_decision(State* state);
};

#endif // SLAMMY_WHAMMY_IMPROVED_H_
