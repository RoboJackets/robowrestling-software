#include <Arduino.h>
#include <util.h>
#include "lineReader.h"

lineReader::lineReader(){
    value = 0;
    threshold = 0;
    counter = 0;
    for (int i = 0; i < 10; i++){
        readings[i] = 0;
    }
};
lineReader::lineReader(int value){
    this->value = value;
    threshold = 0;
    counter = 0;
    for (int i = 0; i < 10; i++){
        readings[i] = 0;
    }
};
int lineReader::getValue(){
    return value;
};
void lineReader::setValue(int reading){
    readings[counter] = reading;
    counter = (counter + 1) % 10;
    value = util::average(readings, 10);
};
int lineReader::getThreshold(){
    return threshold;
};
void lineReader::setThreshold(int threshold){
    this->threshold = threshold;
};