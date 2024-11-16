#ifndef FILTER_H
#define FILTER_H

enum Preference { // this will set the preference of the sensor to read up or down on hazy readings.
    Up,
    Down
};

class Filter {
private:
    int concurrent_count_threshold; // number that count has to reach before changing sensor value.
    int current_count;
    Preference preference;
public:
    Filter(int threshold, Preference preference_value);
    int filterSensor(int sensorValue); // returns clean sensor value.
};

#endif