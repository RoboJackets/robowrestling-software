#include "gucci.h"

State curr_state;
State last_state;

void setup() {
  //setup_imu();
  setup_distance();
  //setup_current();
  setup_motors();
  //attachInterrupt(LEFT_ENCODER, increment_encoder_left, RISING);
  //attachInterrupt(RIGHT_ENCODER, increment_encoder_right, RISING);
}

void loop() {
  curr_state = state_machine(last_state);
  switch(curr_state) {
        case SEARCH_LEFT:

            drive(100, 100, 1, 0);

        case SEARCH_RIGHT:

            drive(100, 100, 0, 1);

        case ADJUST_LEFT:

            drive(100, 80, 0, 0);

        case ADJUST_RIGHT:

            drive(80, 100, 0, 0);

        case SLAMMY_WHAMMY:

            drive(110, 110, 0, 0);

        case PANIC_HIT:

            

        case PANIC_FIRE:

            

        case WAIT_FOR_START:

//            while(waiting) {
//                Serial.println("Waiting");
//            }


        case STARTUP:
            delay(500);
            do_startup_action();

    }

}
