#include "motorDriver.h"
#include <Arduino.h>

//i copilioted all this, read datasheet later

class motorDriver {
    private:
        int speed;
        int direction;
    public:
        motorDriver(){
            speed = 0;
            direction = 0;
        };
        void setSpeed(int speed){
            this->speed = speed;
        };
        void setDirection(int direction){
            this->direction = direction;
        };
        void stop(){
            this->speed = 0;
            this -> direction = 0;
        };
        int getSpeed(){
            return this->speed;
        };
        bool getDirection(){
            return this->direction;
        };
};