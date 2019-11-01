#include "kirbi.h"

State curr_state;
State last_state;

ICM20948 icm(Wire2, (uint8_t)0x68);

void setup() {
  setup_imu();
  setup_distance();
  setup_current(); //???
  setup_motors();
}

void loop() {
  curr_state = state_machine(last_state);
  switch(curr_state) {
        SEARCH_LEFT:

            drive(-x, x);

        SEARCH_RIGHT:

            drive(x, -x);

        ADJUST_LEFT:

            drive(x, y);

        ADJUST_RIGHT:

            drive(y, x);

        SLAMMY_WHAMMY:

            drive(x, x);

        PANIC_HIT:

            dance();

        PANIC_FIRE:

            dance();

        WAIT_FOR_START:

            while(waiting) {
                Serial.println("Waiting");
            }


        STARTUP:
            delay(500);
            do_startup_action();

    }
    
}
