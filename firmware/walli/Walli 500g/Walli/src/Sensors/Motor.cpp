#include <Sensors/Motor.h>
//PLEASE CORRECT THIS IS YOU NOTICE ITS WRONG
//I WENT THROUGH THE DATA SHEETS FOR THE PARTS BUT 
//NOTHING MADE SENSE

//constructor
Motor::Motor(int forward_pin, int backward_pin) {
    _forward_pin = forward_pin;
    _backward_pin = backward_pin;
    //pins are set to INPUT by default, so need to set to OUTPUT
    pinMode(_forward_pin, OUTPUT);
    pinMode(_backward_pin, OUTPUT);
}

//activate forward motor and deactivate backward motor
void Motor::forwards() {
    //digitalWrite(PIN, VALUE) is the method used to manually update an OUTPUT pin
    analogWrite(_forward_pin, 1);
    analogWrite(_backward_pin, 0);
}

//activate backward motor and deactivate forward motor
void Motor::backwards() {
    analogWrite(_forward_pin, 0);
    analogWrite(_backward_pin, 1);
}

//apparently both motors on at the same time turns them off???
//that feels so wrong but help
void Motor::off() {
    analogWrite(_forward_pin, 1);
    analogWrite(_backward_pin, 1);
}
