#ifndef MUX

#define MUX

#include <Sensors/TFMini/TFMini.h>
#include <Arduino.h>
#include "TFMini/TFMini.h"
#include <utility> 


/***
 * This is a class to control the muxes attached to two lidars. 
 * 
 * 
 * 
 * Example code to read from both lidars (attached to a mux) in a loop
        Before Setup:
            TFMini* tfMini;
            LidarMux* mux1;
        Setup:
            tfMini = new TFMini(9, 10);
             mux1 = new LidarMux(25, tfMini);
        Before Loop:
            String out1 = "Lidar one: ";
            String out2 = ", Lidar two: ";
            struct twoValues* x = new twoValues;
        In Loop:
            mux1->readLidars(x);
            String out =  out1 + x->lidarOne + out2 + x->lidarTwo;
            Serial.println(out);
}
*/

struct LidarData {
    int dist; 
    long int timestamp; 
};

class LidarMux {
    private:
        int _muxPin;
        TFMini* _tfmini;
        LidarData _one; 
        LidarData _two; 


        void setHigh() {
            digitalWrite(_muxPin, HIGH);
        }

        void setLow() {
            digitalWrite(_muxPin, LOW);
        }
    
    public:
        LidarMux(int pin) {
            _muxPin = pin;
            pinMode(_muxPin, INPUT);
        }

        LidarMux(int pin, TFMini* mini) {
            _muxPin = pin; 
            _tfmini = mini; 
        }

        std::pair<LidarData, LidarData> readLidars() {
            setLow();
            _tfmini->Poll();
            _one.dist = _tfmini->GetDistance(); 
            _one.timestamp = 0; //TODO: give it a timestamp 
            setHigh();
            _tfmini->Poll();
            _two.dist = _tfmini->GetDistance(); 
            _two.timestamp = 0; 
            auto values = std::make_pair(_one, _two); 
            return values;
        }
        /**
         * Use this if need clocking?
         * 
        */
        std::pair<LidarData, LidarData> readLidars(int clock) {
            if (!clock) {
                setLow();
                 _tfmini->Poll();
                _one.dist = _tfmini->GetDistance(); 
                _one.timestamp = 0; //TODO: give it a timestamp 
            }
            else {
                setHigh();
                _tfmini->Poll();
                _two.dist = _tfmini->GetDistance(); 
                _two.timestamp = 0; 
            }           
            return std::make_pair(_one, _two);
        }


};

#endif