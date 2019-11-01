#include "kirbi.h"
#include "Arduino.h"

#define LIDAR_SERIAL Serial1 

enum State {
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


State state_machine(State lastState) {
    curr_time = millis();
    get_distances();
    get_current();
    if (curr_time - prev_time > check_accel) {
        prev_time = millis();
        get_accel();
    }
    if() {

    } else if () {

    } else if (lastState == WAIT_FOR_START) {
        return STARTUP;
    }

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

//Method for startup action
void do_startup_action() {
    //TODO: implement
}

/**
 * SETUP METHODS
**/

 void setup_imu() {

 }

 void setup_distance() {
     /* lidar setup */
     LIDAR_SERIAL.begin(115200);
     LIDAR_SERIAL.write(configUART, 5);
     LIDAR_SERIAL.write(configOutput, 5);
 }

 void setup_current() {
    // ignore for now
 }

 void setup_motors(){
     // TODO: implement
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
