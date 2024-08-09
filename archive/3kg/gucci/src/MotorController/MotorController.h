#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H
#include <Arduino.h>
#include <stdexcept>
#include <SoftwareSerial.h>

/*
    Simplified serial motor controller mode

    Value of 1-127 commands motor 1
    Value of 128-255 commands motor 2
    Value of 0 sends full stop to both motors

    Functions take a value of -100 to 100 and map it
    for arcade drive.
*/
#define PIN_S1 0
#define PIN_S2 1

class MotorController {
    public:
        MotorController(Stream* serial) {
            _serial = serial;
            _last_turn_speed = 0;
            _last_move_speed = 0;
        }

        /*
            Takes a range from -100 to 100 and translates that into robot movement.
            Uses arcade drive.
            -100 is full backwards, 0 is full stop, 100 is full forwards.

            **WILL RETURN AND DO NOTHING IF VALUE IS NOT IN THE PROPER RANGE**
        */
        void move(int speed) {
            // Protect from improper values
            if (speed < -100 || speed > 100) return;
            _last_move_speed = speed;

            int mapped_first = map(speed, -100, 100, 1, 127);
            int mapped_second = map(speed, -100, 100, 128, 255);
            uint8_t msg[2]; 
            msg[0] = 127; 
            msg[1] = 255;
            _serial -> write(msg, 2);
        }

        void move(int leftSpeed, int rightSpeed) {
            if (leftSpeed < -100 || leftSpeed > 100) return; 
            if (rightSpeed < -100 || rightSpeed > 100) return; 

            int mappedLeft = map(leftSpeed, -100, 100, 1, 127); 
            int mappedRight = map(rightSpeed, -100, 100, 128, 255); 
            uint8_t msg[2]; 
            msg[0] = mappedLeft; 
            msg[1] = mappedRight;
            _serial -> write(msg, 2);
        }
        

        /*
            Takes a range from -100 to 100 and translates that into robot movement.
            Uses arcade drive.
            -100/100 is full one directon, 0 is full stop.
            Direction depends on which motor is motor 1 and which motor is motor 2.

            **WILL RETURN AND DO NOTHING IF VALUE IS NOT IN THE PROPER RANGE**
        */
        void turn(int speed) {
            // Protect from improper values
            if (speed < -100 || speed > 100) return;
            if (speed == _last_turn_speed) return;
            _last_turn_speed = speed;

            int mapped_first = map(speed, -100, 100, 1, 127);
            int mapped_second = -1 * (map(speed, -100, 100, 128, 255)); // Inverted so motors spin opposite directions
            _serial -> write(mapped_first);
            _serial -> write(mapped_second);
        }

        /*
            Shortcut for move(0)
        */
        void stop() {
            uint8_t speeds[2]; 
            speeds[0] = 64; 
            speeds[1] = 192; 
            _serial -> write(speeds, 2); 
        }

    protected:
        //HardwareSerial* _serial;
        Stream* _serial;

        // These need to be separate. Why?
        // What if we move at 50% speed but then want to turn at 50% speed?
        // If we had one value, it would say "oh the last speed was 50%, so don't write anything"
        int _last_move_speed;
        int _last_turn_speed;

};

#endif
