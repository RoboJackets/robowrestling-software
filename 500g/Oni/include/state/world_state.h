#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "../state/sensors/irsensor.h"
#include "../state/sensors/linesensor.h"
#include "../enums/state_enums.h"

class world_state{
    private:
        LINESENSOR * line_left;
        LINESENSOR * line_right;

        IRSENSOR * ir_middle;
        IRSENSOR * ir_middle_left;
        IRSENSOR * ir_middle_right;

    public:
        world_state(LINESENSOR * line_left, LINESENSOR * line_right, IRSENSOR * ir_middle, IRSENSOR * ir_middle_left, IRSENSOR * ir_middle_right);

        SelfPosition line_state();
        EnemyPosition enemy_location();

};

#endif