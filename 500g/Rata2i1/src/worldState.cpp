#include "worldState.h"

//shorti worldstate
worldState::worldState(worldState::joebotSensors sensors){
    this->frontLeftLineSensor = sensors.frontLeftLineSensor;
    this->frontRightLineSensor = sensors.frontRightLineSensor;
    this->frontLeftIRSensor = sensors.frontLeftIRSensor;
    this->frontRightIRSensor = sensors.frontRightIRSensor;
    this->lSide = sensors.Lside;
    this->rSide = sensors.Rside;
    EnemyPosition = Position::MIDDLE_FRONT;
}

worldState::worldState(worldState::xanderSensors sensors){
    this->frontLeftLineSensor = sensors.frontLeftLineSensor;
    this->frontRightLineSensor = sensors.frontRightLineSensor;
    this->frontLeftIRSensor = sensors.frontLeftIRSensor;
    this->frontRightIRSensor = sensors.frontRightIRSensor;
    EnemyPosition = Position::MIDDLE_FRONT;
}

// //joebot worldstate
// worldState::worldState(worldState::joebotSensors sensors){
//     this->frontLeftLineSensor = sensors.frontLeftLineSensor;
//     this->frontRightLineSensor = sensors.frontRightLineSensor;
//     this->backLeftLineSensor = sensors.backLeftLineSensor;
//     this->backRightLineSensor = sensors.backRightLineSensor;
//     this->frontLeftIRSensor = sensors.frontLeftIRSensor;
//     this->frontRightIRSensor = sensors.frontRightIRSensor;
//     this->lSide = sensors.Lside;
//     this->rSide = sensors.Rside;
//     this->mSensor = sensors.MSensor;
//     EnemyPosition = Position::MIDDLE_FRONT;
// }

// worldState::worldState(worldState::robotSensors sensors){
//     this->frontLeftLineSensor = sensors.frontLeftLineSensor;
//     this->frontRightLineSensor = sensors.frontRightLineSensor;
//     this->backLeftLineSensor = sensors.backLeftLineSensor;
//     this->backRightLineSensor = sensors.backRightLineSensor;
//     this->frontLeftIRSensor = sensors.frontLeftIRSensor;
//     this->frontRightIRSensor = sensors.frontRightIRSensor;
//     this->backLeftIRSensor = sensors.backLeftIRSensor;
//     this->backRightIRSensor = sensors.backRightIRSensor;
//     EnemyPosition = Position::MIDDLE_FRONT;
// }

Position worldState::getEnemyPosition(){
    int frontLeft = frontLeftIRSensor->getValue();
    int frontRight = frontRightIRSensor->getValue();
    int backLeft = backLeftIRSensor->getValue();
    int backRight = backRightIRSensor->getValue();
    if(frontLeft && frontRight) {
        EnemyPosition = Position::MIDDLE_FRONT;
    } else if(frontLeft) {
        EnemyPosition = Position::FRONT_LEFT;
    } else if(frontRight) {
        EnemyPosition = Position::FRONT_RIGHT;
    } else if(backLeft && backRight) {
        EnemyPosition = Position::MIDDLE_BACK;
    } else if(backLeft) {
        EnemyPosition = Position::BACK_LEFT;
    } else if(backRight) {
        EnemyPosition = Position::BACK_RIGHT;
    } else {
        EnemyPosition = Position::NONE;
    }
    return EnemyPosition;
}

Position worldState::getPosition(){
    int frontLeft = frontLeftIRSensor->getValue();
    int frontRight = frontRightIRSensor->getValue();
    // int backLeft = backLeftIRSensor->getValue();
    // int backRight = backRightIRSensor->getValue();
    int backLeft = 0;
    int backRight = 0;
    if (frontLeft && frontRight) {
        return Position::ON_LINE_FRONT;
    } else if (frontLeft) {
        return Position::ON_LINE_FRONT_LEFT;
    } else if (frontRight) {
        return Position::ON_LINE_FRONT_RIGHT;
    } else if (backLeft && backRight) {
        return Position::ON_LINE_BACK;
    } else if (backLeft) {
        return Position::ON_LINE_BACK_LEFT;
    } else if (backRight) {
        return Position::ON_LINE_BACK_RIGHT;
    } else {
        return Position::NONE;
    }
}