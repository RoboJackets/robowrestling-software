#ifndef MUX

#define MUX

#include <Arduino.h>
#include "TFMini/TFMini.h"

struct twoValues {
    int lidarOne;
    int lidarTwo;
};


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



class LidarMux {
    private:
        int _muxPin;
        TFMini* _tfmini;
        void setHigh() {
            digitalWrite(_muxPin, HIGH);
        }
        void setLow() {
            digitalWrite(_muxPin, LOW);
        }
    
    public:
        LidarMux(int muxPin, TFMini* tfmini) {
            _tfmini = tfmini;
            _muxPin = muxPin;
            pinMode(_muxPin, OUTPUT);
            setLow();
        }

        LidarMux(int muxPin, int rx, int tx) {
            _tfmini = new TFMini(rx, tx);
            _muxPin = muxPin;
            pinMode(_muxPin, OUTPUT);
            setLow();
        }

        struct twoValues* readLidars() {
            setLow();
            _tfmini->Poll();
            int one = _tfmini->GetDistance();
            setHigh();
            _tfmini->Poll();
            int two = _tfmini->GetDistance();
            struct twoValues* values = (struct twoValues*) malloc(sizeof(struct twoValues));
            values->lidarOne = one;
            values->lidarTwo = two;
            return values;
        }

        struct twoValues* readLidars(struct twoValues* pointer) {
            setLow();
            _tfmini->Poll();
            int one = _tfmini->GetDistance();
            setHigh();
            _tfmini->Poll();
            int two = _tfmini->GetDistance();
            pointer->lidarOne = one;
            pointer->lidarTwo = two;
            return pointer;
        }
        /**
         * Use this if need clocking?
         * 
        */
        struct twoValues* readLidars(struct twoValues* pointer, int clock) {
            if (!clock) {
                setLow();
                 _tfmini->Poll();
                 int one = _tfmini->GetDistance();
                  pointer->lidarOne = one;
            }
            else {
                setHigh();
                _tfmini->Poll();
                int two = _tfmini->GetDistance();
                pointer->lidarTwo = two;
            }           
            return pointer;
        }


};

#endif