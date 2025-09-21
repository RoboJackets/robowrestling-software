#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
    private:
        int value;
        int concurrency;
    public:
        Sensor();
        int getValue();
        void setValue(int sensorValue);
    
};

#endif
