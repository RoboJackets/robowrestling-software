#include<Sensors/Lidar.cpp>
#include<Sensors/LineSensor.cpp>
#include<Sensors/Motor.cpp>
#include <Arduino.h>
#include <SoftwareSerial.h>

class Walli {
    private:
        Lidar leftLidar;
        Lidar centerLidar;
        Lidar rightLidar;
        LineSensor topLeftLine;
        LineSensor topRightLine;
        LineSensor bottomLeftLine;
        LineSensor bottomRightLine;
        Motor leftMotor;
        Motor rightMotor;
    public:
        Walli(int leftLidarPin, int centerLidarPin, int rightLidarPin, 
                int topLeftLinePin, int topRightLinePin, 
                int bottomLeftLinePin, int bottomRightLinePin,
                int leftMotorPin1, int leftMotorPin2, 
                int rightMotorPin1, int rightMotorPin2);
        void turnLeft();
        void turnRight();
        void reverse();
        void forward();
        void off();
        bool onFrontLine();
        bool onBackLine();
        bool leftDetected();
        bool centerDetected();
        bool rightDetected();
};