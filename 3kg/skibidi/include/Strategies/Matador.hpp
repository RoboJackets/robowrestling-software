#ifndef MATADOR_H_
#define MATADOR_H_

#include "Strategies/Strategy.hpp"
#include "Strategies/Track.hpp"
#include "Strategies/SlammyWhammyImproved.hpp"

#define TURN_MILLIS 50  // tune on bot to find best value
#define REVERSE_MILLIS 300

class Matador : public Strategy {
    public:
        Matador(int charge_speed, int rev_speed);
        void make_decision(State* state);

    private:
        int charge_speed, rev_speed, millis_tracker = 0;
        bool initiated_matador = false, turn_complete = false, rev_complete = false;
        Track track = Track(50, 35);
        SlammyWhammy slammy_whammy = SlammyWhammy(50, 35);
};

#endif // MATADOR_H_
