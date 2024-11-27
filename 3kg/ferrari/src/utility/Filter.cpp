#include "utility/Filter.hpp"

Filter::Filter(bool sensorType) {
    values = new queue<int>();
    isDigital = sensorType;
}

/**
 * returns high if rolling sum is greater than 5 and
 * low if rolling sum is less than 5.
 */
void Filter::filterSensor(int rawSensorValue) {
    if (values->size() < 10) {
        values->push(rawSensorValue);
    } else {
        rollingSum -= values->front();
        values->pop();
        values->push(rawSensorValue);
    }
    rollingSum += rawSensorValue;
}

int Filter::getSensorValue() {
    if (isDigital) {
        return rollingSum > 5 ? 1 : 0;
    } else { // is analog (5 x 1000) // maybe make this value adjustable if not dynamically set at the start of the match.
        return rollingSum > 5000 ? 1 : 0;
    }
}