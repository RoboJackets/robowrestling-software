#include "utility/Filter.h"

Filter::Filter(int threshold, Preference preference_value) {
    concurrent_count_threshold = threshold;
    preference = preference_value;
}

int Filter::filterSensor(int sensorValue) {
    
}