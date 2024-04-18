#include<Robot/Walli.h>

/* This is the class that controls Walli's specific behavior.
* This is where all the pins are initialized
* and controlled
*/

//constructor
Walli::Walli(int leftLidarPin, int centerLidarPin, int rightLidarPin, 
                int topLeftLinePin,  
                int bottomLeftLinePin, int bottomRightLinePin,
                int leftMotorPin1, int leftMotorPin2, 
                int rightMotorPin1, int rightMotorPin2) {
    //change to this->
    this->leftLidar = new Lidar(leftLidarPin);
    this->centerLidar = new Lidar(centerLidarPin);
    this->rightLidar = new Lidar(rightLidarPin);
    this->topLeftLine = new LineSensor(topLeftLinePin);
    this->bottomLeftLine = new LineSensor(bottomLeftLinePin);
    this->bottomRightLine = new LineSensor(bottomRightLinePin);
    this->leftMotor = new Motor(leftMotorPin1, leftMotorPin2);
    this->rightMotor = new Motor(rightMotorPin1, rightMotorPin2);
}

//have the left wheel go backwards and the right wheel forwards
void Walli::turnLeft() {
    leftMotor->backwards();
    rightMotor->forwards();
}

//have the left wheel go forwrds and the right wheel backwards
void Walli::turnRight() {
    leftMotor->forwards();
    rightMotor->backwards();
}

//have the left wheel go backwards and the right wheel backwards
void Walli::reverse() {
    leftMotor->backwards();
    rightMotor->backwards();
}

//have the left wheel go forwards and the right wheel forwards
void Walli::forward() {
    leftMotor->forwards();
    rightMotor->forwards();
}

//have the left wheel go backwards and the right wheel forwards
void Walli::off() {
    leftMotor->off();
    rightMotor->off();
}

//detect if either of the upper sensors are on the line
bool Walli::onFrontLine() {
    return topLeftLine->onLine();
}
//detect if either of the lower  sensors are on the line
bool Walli::onBackLine() {
    return bottomLeftLine->onLine() || bottomRightLine->onLine();
}

//detect if the left lidar is detected something
bool Walli::leftDetected() {
    return leftLidar->detected();
}
//detect if the center  lidar is detected something
bool Walli::centerDetected() {
    return centerLidar->detected();
}
//detect if the right lidar is detected something
bool Walli::rightDetected() {
    return rightLidar->detected();
}