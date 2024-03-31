#include<Robot/Walli.h>

Walli::Walli(int leftLidarPin, int centerLidarPin, int rightLidarPin, 
                int topLeftLinePin, int topRightLinePin, 
                int bottomLeftLinePin, int bottomRightLinePin,
                int leftMotorPin1, int leftMotorPin2, 
                int rightMotorPin1, int rightMotorPin2) {
    Walli::leftLidar = new Lidar(leftLidarPin);
    Walli::centerLidar = new Lidar(centerLidarPin);
    Walli::rightLidar = new Lidar(rightLidarPin);
    Walli::topLeftLine = new LineSensor(topLeftLinePin);
    Walli::topRightLine = new LineSensor(topRightLinePin);
    Walli::bottomLeftLine = new LineSensor(bottomLeftLinePin);
    Walli::bottomRightLine = new LineSensor(bottomRightLinePin);
    Walli::leftMotor = new Motor(leftMotorPin1, leftMotorPin2);
    Walli::rightMotor = new Motor(rightMotorPin1, rightMotorPin2);
}

void Walli::turnLeft() {
    leftMotor->backwards();
    rightMotor->forwards();
}

void Walli::turnRight() {
    leftMotor->forwards();
    rightMotor->backwards();
}

void Walli::reverse() {
    leftMotor->backwards();
    rightMotor->backwards();
}

void Walli::forward() {
    leftMotor->forwards();
    rightMotor->forwards();
}

void Walli::off() {
    leftMotor->off();
    rightMotor->off();
}

bool Walli::onFrontLine() {
    return topLeftLine->onLine() || topRightLine->onLine();
}

bool Walli::onBackLine() {
    return bottomLeftLine->onLine() || bottomRightLine->onLine();
}

bool Walli::leftDetected() {
    return leftLidar->detected();
}

bool Walli::centerDetected() {
    return centerLidar->detected();
}

bool Walli::rightDetected() {
    return rightLidar->detected();
}