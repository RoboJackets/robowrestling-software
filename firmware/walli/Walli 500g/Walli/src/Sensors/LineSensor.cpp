#include<Sensors/LineSensor.h>

int LineSensor::sample() {
    int floorReading = 0;
    int samples = 0;
    for (int i = 0; i < 25; i++) {
        floorReading += WalliSensor::read();
        samples++;
    }
    return floorReading/samples; 
}
LineSensor::LineSensor(int pin):WalliSensor(pin) {
    _base = sample();
    _threshold = 3;
}

bool LineSensor::onLine() {
    return abs(WalliSensor::read() - _base) >= _threshold;
}