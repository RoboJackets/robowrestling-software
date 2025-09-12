#ifndef SLAMMY_WHAMMY_MODULAR_H_
#define SLAMMY_WHAMMY_MODULAR_H_

#include "Strategies/Strategy.hpp"

class SlammyWhammyModular : public Strategy {
    private:
        // ChargeAction charge;
        // SeekAction seek;
        // int current_state = 0;  // enum?
    public:
        SlammyWhammyModular();

        void make_decision(State* state);
};

#endif // SLAMMY_WHAMMY_MODULAR_H_
