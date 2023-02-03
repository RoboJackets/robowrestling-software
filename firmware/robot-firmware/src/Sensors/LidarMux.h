#ifndef MUX

#define MUX

#include <Arduino.h>
#include "TFMini/TFMini.h"

struct twoValues {
    int lidarOne;
    int lidarTwo;
};

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
            pinMode(_muxPin, INPUT);
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


};

#endif