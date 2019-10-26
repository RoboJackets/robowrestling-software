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


States state_machine(States lastState) {
    // TODO: implement
}

void drive(int left, int right) {
    // TODO: implement
}

/**
 * INTERRUPT METHODS
**/
void do_line_action_left() {
    //TODO: implement
}
void do_line_action_right() {
    //TODO: implement
}
void do_startup_action() {
    //TODO: implement
}

/**
 * SENSOR READ METHODS
**/
void get_accel() {
    //TODO: implement
}
void get_gyro() {
    //TODO: implement
}
void get_distances() {
    //TODO: implement
}
void get_current() {
    // ignore for now
}
