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
//            drive(100, 100, 1, 0);
              Serial.println("SL");
              break;
        case SEARCH_RIGHT:
              Serial.println("SR");

//            drive(100, 100, 0, 1);
              break;

        case ADJUST_LEFT:
              Serial.println("AL");

//            drive(100, 80, 0, 0);
              break;
        case ADJUST_RIGHT:
              Serial.println("AR");

//            drive(80, 100, 0, 0);
              break;
        case SLAMMY_WHAMMY:
              Serial.println("Come on and slam");

//            drive(110, 110, 0, 0);
              break;
        case PANIC_HIT:

            
              break;
        case PANIC_FIRE:

            
              break;
        case WAIT_FOR_START:

//            while(waiting) {
//                Serial.println("Waiting");
//            }

              break;
        case STARTUP:
            delay(500);
            do_startup_action();
            break;
    }

}
