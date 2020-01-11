#include "kirbi.h"

State curr_state;

void setup()
{
//      setup_imu();
//      setup_distance();
      setup_motors();
//      setup_encoders();
//      setup_line();
      setup_remote();
      pinMode(13, OUTPUT);
      //while (!digitalRead(REMOTE_PIN)) {
      // Serial.println("Waiting");
      //}
      // delay(500);
      Serial.begin(115200);
      Serial.println("finished setup");

}

void loop()
{
      if (digitalRead(REMOTE_PIN))
      {     
            Serial.println("doing startup action");
            do_startup_action();
            while (digitalRead(REMOTE_PIN))
            {
//                  if (get_line_flag())
//                  {
//                        drive(-30, -30);
//                        delay(200);
////                        Serial.println("Line!");
//                  }
//                  else
//                  { 
                        curr_state = SLAMMY_WHAMMY; //for testing purposes only
//                        curr_state = state_machine();
                        //Serial.println(digitalRead(LEFT_INT_LINE));
                        //Serial.println(digitalRead(RIGHT_INT_LINE));
                        //Serial.println(digitalRead(REMOTE_PIN));
                        switch (curr_state)
                        {
                        case SEARCH:
                             
//                              Serial.println("SEARCH");
                              drive(-50, 50);
                              break;
                        case ADJUST_1_LEFT:
//                              Serial.println("A1L");

                              drive(10, -10);
                              break;
                        case ADJUST_1_RIGHT:
//                              Serial.println("A1R");

                               drive(-10, 10);
                              break;
                        case ADJUST_2_LEFT:
//                              Serial.println("A2L");

                               drive(20, -20);
                              break;
                        case ADJUST_2_RIGHT:
//                              Serial.println("A2R");

                              drive(-20, 20);
                              break;
                        case ADJUST_3_LEFT:
//                              Serial.println("A3L");

                              drive(30, -30);
                              break;
                        case ADJUST_3_RIGHT:
//                              Serial.println("A3R");

                              drive(-30, 30);
                              break;
                        case ADJUST_4_LEFT:
//                              Serial.println("A4L");

                              drive(40, -40);
                              break;
                        case ADJUST_4_RIGHT:
//                              Serial.println("A4R");

                              drive(-40, 40);
                              break;
                        case SLAMMY_WHAMMY:
//                              Serial.println("Come on and slam");

                              drive(55, 55);
                              break;
                        case MEGA_SLAMMY_WHAMMY:
//                              Serial.println("Kirbi used Skull Bash. It was super effective!");
                              drive(63,63);
                              break;
                        case PANIC_HIT:
                              // drive(-40, -100);
//                              Serial.println("We're hit captain!");
                              break;
                        case PANIC_FIRE:
                              drive(0, 0);
//                              Serial.println("AGHHHHHHHHHH FIREEEE");
                              break;
//                        }
                  }
            }
//            Serial.println("END SIGNAL");
            drive(0,0);
//
      }
//      get_distances();
//      delay(1000);
}
