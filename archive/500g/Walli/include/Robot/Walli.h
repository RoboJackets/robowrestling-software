#ifndef WALLI
#define WALLI
#include<Sensors/Lidar.h>
#include<Sensors/LineSensor.h>
#include<Sensors/Motor.h>


class Walli {
    private:
        Lidar* leftLidar;
        Lidar* centerLidar;
        Lidar* rightLidar;
        LineSensor* topLeftLine;
        LineSensor* bottomRightLine;
        Motor* leftMotor;
        Motor* rightMotor;
    public:
        Walli(int leftLidarPin, int centerLidarPin, int rightLidarPin, 
                int topLeftLinePin,int bottomRightLinePin,
                int leftMotorPin1, int leftMotorPin2, 
                int rightMotorPin1,int rightMotorPin2);
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
#endif