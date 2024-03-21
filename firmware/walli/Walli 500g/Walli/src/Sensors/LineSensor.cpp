#include<Sensors/Sensor.cpp>

class LineSensor : public Sensor {
    private:
        int _base;
        int _threshold;
        int sample() {
            int floorReading = 0;
            int samples = 0;
            for (int i = 0; i < 25; i++) {
                floorReading += Sensor::read();
                samples++;
            }
            return floorReading/samples; 
        }
    public:
        LineSensor(int pin):Sensor(pin) {
            _base = sample();
            _threshold = 3;
        }

        bool onLine() {
            return abs(Sensor::read() - _base) >= _threshold;
        }

        


};