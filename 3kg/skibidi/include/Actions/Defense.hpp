#ifndef DEFENSE_HPP_
#define DEFENSE_HPP_

#include "Actions/Action.hpp"

#define FLINCH_MILLIS 100

class Defense : public Action {
    private:
        bool have_flinched;
        int flinch_started_millis;
    public:
        Defense();
        virtual void make_decision(State* state);
};

#endif // DEFENSE_HPP_
