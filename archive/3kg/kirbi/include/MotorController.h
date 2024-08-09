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

    For the above ranges, the minimum of the range (i.e. 1 for motor 1)
    translates to full reverse, while the maximum of the
    range (i.e. 127 for motor 1) translates to full forwards.
    The value to stop the motor is the one in the middle of the range.

    Functions take a value of -100 to 100 and map it
    for arcade drive.
*/
#define PIN_S1 0
#define PIN_S2 1

class MotorController {
public:
    MotorController(Stream* serial);
    /*
        Takes a range from -100 to 100 and translates that into robot movement.
        Uses arcade drive.
        -100 is full backwards, 0 is full stop, 100 is full forwards.

        **WILL RETURN AND DO NOTHING IF VALUE IS NOT IN THE PROPER RANGE**
    */
    void move(int speed);
    void move(int leftSpeed, int rightSpeed);

    /*
        Takes a range from -100 to 100 and translates that into robot movement.
        Uses arcade drive.
        -100/100 is full one directon, 0 is full stop.
        Direction depends on which motor is motor 1 and which motor is motor 2.

        **WILL RETURN AND DO NOTHING IF VALUE IS NOT IN THE PROPER RANGE**
    */
    void turn(int speed);

    /*
        Shortcut for move(0)
    */
    void stop();

protected:
    //HardwareSerial* _serial;
    Stream* _serial;

    // These need to be separate. Why?
    // What if we move at 50% speed but then want to turn at 50% speed?
    // If we had one value, it would say "oh the last speed was 50%, so don't write anything"
    int _last_move_speed;
    int _last_turn_speed;

    void _sendCommand(int leftSpeed, int rightSpeed);

};

#endif
