#include "kirbi.h"
#include "Arduino.h"

enum States {
    SEARCH_LEFT,
    SEARCH_RIGHT,
    ADJUST_LEFT,
    ADJUST_RIGHT,
    SLAMMY_WHAMMY,

    PANIC_HIT,
    PANIC_FIRE,

    WAIT_FOR_START,
    STARTUP
};



States dispatcher(States lastState, ) {
    // read sensors
}
