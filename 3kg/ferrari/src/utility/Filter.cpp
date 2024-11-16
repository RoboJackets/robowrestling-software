#include "utility/Filter.hpp"

int Filter::FilterSensor(int rawSensorValue) {
    if (values.size() < 10) {
        values.push(rawSensorValue);
    } else {
        rollingSum -= values.front();
        values.pop();
        values.push(rawSensorValue);
    }
    rollingSum += rawSensorValue;
}