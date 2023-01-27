#ifndef MUX

#define MUX

#include <Arduino.h>

struct twoValues {
    int lidarOne;
    int lidarTwo;
};

class LidarMux {
    private:
        int _muxPin;
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

        struct twoValues* readLidars() {
            setLow();
            int one = read1();
            setHigh();
            int two = read2();
            struct twoValues* values = (struct twoValues*) malloc(sizeof(struct twoValues));
            values->lidarOne = one;
            values->lidarTwo = two;
            return twoValues;
        }

        struct twoValues* readLidars(struct twoValues* pointer) {
            setLow();
            int one = read();
            setHigh();
            int two = read();
            pointer->lidarOne = one;
            pointer->lidarTwo = two;
            return pointer;
        }


};

#endif