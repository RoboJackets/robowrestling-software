#ifndef DEFENSE_HPP_
#define DEFENSE_HPP_

#include "Strategies/Strategy.hpp"

#define FLINCH_MILLIS     100
#define UNTIL_INCH_MILLIS 3000
#define INCH_MILLIS       50
#define INCH_WAIT_MILLIS  1000

enum Phase {
  PRE_FLINCH, FLINCHING,
  PRE_INCH, INCH_START, INCH_FWD, INCH_WAIT,
  CHARGING
};

class Defense : public Strategy {
    private:
        enum Phase phase;
        int flinch_started_millis;
        int inch_started_millis;
    public:
        Defense();
        void make_decision(State* state);
};

#endif // DEFENSE_HPP_
