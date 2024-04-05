#include<Robot/Walli.h>

Walli::Walli(int leftLidarPin, int centerLidarPin, int rightLidarPin, 
                int topLeftLinePin, int topRightLinePin, 
                int bottomLeftLinePin, int bottomRightLinePin,
                int leftMotorPin1, int leftMotorPin2, 
                int rightMotorPin1, int rightMotorPin2) {
    //change to this->
    this->leftLidar = new Lidar(leftLidarPin);
    this->centerLidar = new Lidar(centerLidarPin);
    this->rightLidar = new Lidar(rightLidarPin);
    this->topLeftLine = new LineSensor(topLeftLinePin);
    this->topRightLine = new LineSensor(topRightLinePin);
    this->bottomLeftLine = new LineSensor(bottomLeftLinePin);
    this->bottomRightLine = new LineSensor(bottomRightLinePin);
    this->leftMotor = new Motor(leftMotorPin1, leftMotorPin2);
    this->rightMotor = new Motor(rightMotorPin1, rightMotorPin2);
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