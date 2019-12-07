#include "gucci.h"

State curr_state;
State last_state;

void setup() {
  setup_imu();
  setup_distance();
  setup_current();
  setup_motors();
  setup_encoders();
  setup_line();
  setup_remote();

}

void loop() {
  curr_state = state_machine(last_state);
  Serial.println(digitalRead(LL_INT));
  Serial.println(digitalRead(RL_INT));
//  Serial.println(digitalRead(17));
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
    delay(1000);

}
