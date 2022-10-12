#include "Sensor.h"

/*
A class for the TFMini Plus Sensor.
https://cdn.sparkfun.com/assets/2/b/0/3/8/TFmini_Plus-01-A02-Datasheet_EN.pdf 
https://cdn.sparkfun.com/assets/1/4/2/1/9/TFmini_Plus_A02_Product_Manual_EN.pdf
*/
#define tfmpBytesToPoll 9
class TFMini : public Sensor {
    

    public:
        TFMini(int rx, int tx, HardwareSerial* serial) : Sensor(rx, tx, tfmpBytesToPoll, serial){ 
            
        }
};