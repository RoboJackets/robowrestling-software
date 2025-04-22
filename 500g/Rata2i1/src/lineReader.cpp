#include <Arduino.h>
#include <util.h>
#include "lineReader.h"

lineReader::lineReader(){
    value = 0;
    threshold = 100;
    average = 0;
    counter = 0;
    for (int i = 0; i < 10; i++){
        readings[i] = 0;
    }
};
lineReader::lineReader(int value){
    this->value = value;
    threshold = 100;
    counter = 0;
    average = 0;
    for (int i = 0; i < 10; i++){
        readings[i] = 0;
    }
};
lineReader::lineReader(int value, int threshold){
    this->value = value;
    this->threshold = threshold;
    counter = 0;
    average = 0;
    for (int i = 0; i < 10; i++){
        readings[i] = 0;
    }
};
int lineReader::getValue(){
    if (average < threshold){
        return 1;
    }
    else{
        return 0;
    }
};
double lineReader::getAverage(){
    return average;
};
void lineReader::setValue(int reading){
    readings[counter] = reading;
    counter = (counter + 1) % 10;
    average = util::average(readings, 10);
};
int lineReader::getThreshold(){
    return threshold;
};
void lineReader::setThreshold(int threshold){
    this->threshold = threshold;
};