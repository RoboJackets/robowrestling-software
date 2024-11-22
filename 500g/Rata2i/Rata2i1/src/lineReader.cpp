#include <Arduino.h>
#include <util.h>
#include "lineReader.h"

class lineReader {
    private:
        int value;
        int readings[10];
        int threshold;
        int counter;
    public:
        lineReader(){
            value = 0;
            threshold = 0;
            counter = 0;
            for (int i = 0; i < 10; i++){
                readings[i] = 0;
            }
        };
        lineReader(int value){
            this->value = value;
            threshold = 0;
            counter = 0;
            for (int i = 0; i < 10; i++){
                readings[i] = 0;
            }
        };
        int getValue(){
            return value;
        };
        void setValue(int reading){
            readings[counter] = reading;
            counter = (counter + 1) % 10;
            value = util::average(readings, 10);
        };
        int getThreshold(){
            return threshold;
        };
        void setThreshold(int threshold){
            this->threshold = threshold;
        };
};