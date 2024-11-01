#include "../../include/common.h"

Robot::Robot() {}

void Robot::createIMU() {
    this->imu = IMU();
}

void Robot::createDipSwitch(uint8_t pin1, uint8_t pin2) {
    this->dipSwitch = DipSwitch(pin1, pin2);
}

void Robot::createIRSensors(uint8_t pins[5]) {
    this->leftIR = IRSensor(pins[0]);
    this->midLeftIR = IRSensor(pins[1]);
    this->midIR = IRSensor(pins[2]);
    this->midRightIR = IRSensor(pins[3]);
    this->rightIR = IRSensor(pins[4]);
}

void Robot::createLineSensors(uint8_t pins[2]) {
    this->leftLineSensor = LineSensor(pins[0]);
    this->rightLineSensor = LineSensor(pins[1]);
}

void Robot::createMotors(uint8_t leftMotorPins[2], uint8_t rightMotorPins[2]) {
    this->leftMotorDriver = MotorDriver(leftMotorPins[0], leftMotorPins[1]);
    this->rightMotorDriver = MotorDriver(rightMotorPins[0], rightMotorPins[1]);
}

void Robot::createFlags(uint8_t pin) {
    this->flags = Flags(pin);
}

void Robot::createStartModule(uint8_t pin) {
    this->startModule = StartModule(pin);
}

bool Robot::checkBoundary() {
   uint8_t threshold = 60;
   bool leftDetected = this->leftLineSensor.getValue() < threshold;
   bool rightDetected = this->rightLineSensor.getValue() < threshold;
   return leftDetected || rightDetected; 
}

const bool* Robot::getIRValues() {
    return this->irValues;
}

const float* Robot::getPose() {
    return this->orientation;
}

bool Robot::getStartModActivated() {
    return this->startModActivated;
}

void Robot::updateState() {
    this->atBoundary = checkBoundary();

    // IRSensors
    this->irValues[0] = this->leftIR.getValue();
    this->irValues[1] = this->midLeftIR.getValue();
    this->irValues[2] = this->midIR.getValue();
    this->irValues[3] = this->midRightIR.getValue();
    this->irValues[4] = this->rightIR.getValue();

    // IMU
    this->imu.update();
    this->orientation[0] = this->imu.getAngleX();
    this->orientation[1] = this->imu.getAngleY();
    this->orientation[2] = this->imu.getAngleZ();

    this->startModActivated = this->startModule.getActivated();        
}



// motor movement
void Robot::moveForwards(int speed) {
    leftMotorDriver.moveMotor(speed, 0);
    rightMotorDriver.moveMotor(speed, 0);
}

void Robot::moveForwards(int speed, int time) {

    leftMotorDriver.moveMotor(speed, 0);
    rightMotorDriver.moveMotor(speed, 0);
    delay(time);
    brakeHigh();
}

void Robot::moveBackwards(int speed) {
    leftMotorDriver.moveMotor(0, speed);
    rightMotorDriver.moveMotor(0, speed);
}

void Robot::moveBackwards(int speed, int time) {

    leftMotorDriver.moveMotor(0, speed);
    rightMotorDriver.moveMotor(0, speed);
    delay(time);
    brakeHigh();
}

void Robot::turnMove(int speedLeft, int speedRight) {
    leftMotorDriver.moveMotor(speedLeft, 0);
    rightMotorDriver.moveMotor(speedRight, 0);
}

void Robot::brakeHigh() {
    leftMotorDriver.moveMotor(255, 255);
    rightMotorDriver.moveMotor(255, 255);
}

void Robot::turnLeftNoGyro(int speed, int time) {
    leftMotorDriver.moveMotor(0, speed);
    rightMotorDriver.moveMotor(speed, 0);
    delay(time);
    brakeHigh();
}

void Robot::turnRightNoGyro(int speed, int time) {
    leftMotorDriver.moveMotor(speed, 0);
    rightMotorDriver.moveMotor(0, speed);
    delay(time);
    brakeHigh();
}