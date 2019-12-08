#include "kirbi.h"

State curr_state;

void setup() {
  setup_imu();
  setup_distance();
  setup_current();
  setup_motors();
  setup_encoders();
  setup_line();
  setup_remote();
  //while (!digitalRead(REMOTE_PIN)) {
   // Serial.println("Waiting");
  //}
  Serial.println("Hello");
  delay(500);
  do_startup_action();
}

void loop() {
  if (get_line_flag()) {
//    drive(60, 60, 1, 1);
    Serial.println("Line");
  } else {
    curr_state = state_machine();
//    Serial.println(digitalRead(LEFT_INT_LINE));
//    Serial.println(digitalRead(RIGHT_INT_LINE));
//    Serial.println(digitalRead(REMOTE_PIN));
    switch(curr_state) {
          case SEARCH:
  //            drive(100, 100, 1, 0);
                Serial.println("S");
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
                Serial.println("Gucci used Skull Bash. It was super effective!");
                break;
          case PANIC_HIT:
                // drive(40, 100, 1, 1);
                Serial.println("We're hit captain!");
                break;
          case PANIC_FIRE:
                //drive(0, 0, 0, 0);
                Serial.println("AGHHHHHHHHHH");
                break;
    }
  }
}
