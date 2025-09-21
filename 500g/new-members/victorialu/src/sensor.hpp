#ifndef SENSOR_H
#define SENSOR_H

class sensor {
    private:
        int value;
        int concurrency;
    public:
        sensor(int sensorValue);
        int getValue();
        void setValue(int newVal);
};

#endif