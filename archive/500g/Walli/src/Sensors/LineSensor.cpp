#include<Sensors/LineSensor.h>

/*Class that retrieves information from 
* each line sensor.
*/

//read the "floor" so that we can tell the difference
//between the arena and the out-of-bounds line
int LineSensor::sample() {
    int floorReading = 0;
    int samples = 0;
    for (int i = 0; i < 25; i++) {
        floorReading += this->read();
        samples++;
    }
    //take the average of 25 readings
    return floorReading/samples; 
}
//constructor
LineSensor::LineSensor(int pin):WalliSensor(pin) {
    _base = sample();
    _threshold = 3; //this can change
}

//if the difference between the current surface and the floor is too big
//that means we're on the line
bool LineSensor::onLine() {
    return abs(WalliSensor::read() - _base) >= _threshold;
}

void LineSensor::write(int n) {
    this->write(abs(n - _base) >= _threshold);
}