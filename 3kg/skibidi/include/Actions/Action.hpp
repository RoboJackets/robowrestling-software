#ifndef ACTION_H_
#define ACTION_H_

#include "Skibidi.hpp"

class Action {
    public:
        virtual ~Action() {}
        virtual void make_decision(State* state) = 0;
};

#endif // ACTION_H_
