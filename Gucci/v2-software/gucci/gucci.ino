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

        case ADJUST_1_LEFT:
              Serial.println("A1L");

//            drive(20, 0, 0, 0);
              break;
        case ADJUST_1_RIGHT:
              Serial.println("A1R");

//            drive(0, 20, 0, 0);
              break;
        case ADJUST_2_LEFT:
              Serial.println("A2L");

//            drive(40, 0, 0, 0);
              break;
        case ADJUST_2_RIGHT:
              Serial.println("A2R");

//            drive(0, 40, 0, 0);
              break;
        case ADJUST_3_LEFT:
              Serial.println("A3L");

//            drive(60, 0, 0, 0);
              break;
        case ADJUST_3_RIGHT:
              Serial.println("A3R");

//            drive(0, 60, 0, 0);
              break;
        case ADJUST_4_LEFT:
              Serial.println("A4L");

//            drive(80, 0, 0, 0);
              break;
        case ADJUST_4_RIGHT:
              Serial.println("A4R");

//            drive(0, 80, 0, 0);
              break;
        case SLAMMY_WHAMMY:
              Serial.println("Come on and slam");

//            drive(80, 80, 0, 0);
              break;
        case MEGA_SLAMMY_WHAMMY:
              Serial.println("Gucci used Skull Bash. It was super effective!")
        case PANIC_HIT:
              // drive(40, 100, 1, 1);

              break;
        case PANIC_FIRE:
              //drive(0, 0, 0, 0);

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
