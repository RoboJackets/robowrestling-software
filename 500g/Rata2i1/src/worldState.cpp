#include "worldState.h"

worldState::worldState(lineReader *frontLeftLineSensor, lineReader *frontRightLineSensor, lineReader *backLeftLineSensor, lineReader *backRightLineSensor, IRSensor *frontLeftIRSensor, IRSensor *frontRightIRSensor, IRSensor *Rside, IRSensor *Lside, IRSensor *MSensor){
    this->frontLeftLineSensor = frontLeftLineSensor;
    this->frontRightLineSensor = frontRightLineSensor;
    this->backLeftLineSensor = backLeftLineSensor;
    this->backRightLineSensor = backRightLineSensor;
    this->frontLeftIRSensor = frontLeftIRSensor;
    this->frontRightIRSensor = frontRightIRSensor;
    this->lSide = Lside;
    this->rSide = Rside;
    this->mSensor = MSensor;
    EnemyPosition = Position::MIDDLE_FRONT;
}

worldState::worldState(lineReader *frontLeftLineSensor, lineReader *frontRightLineSensor, lineReader *backLeftLineSensor, lineReader *backRightLineSensor, IRSensor *frontLeftIRSensor, IRSensor *frontRightIRSensor, IRSensor *backLeftIRSensor, IRSensor *backRightIRSensor){
    this->frontLeftLineSensor = frontLeftLineSensor;
    this->frontRightLineSensor = frontRightLineSensor;
    this->backLeftLineSensor = backLeftLineSensor;
    this->backRightLineSensor = backRightLineSensor;
    this->frontLeftIRSensor = frontLeftIRSensor;
    this->frontRightIRSensor = frontRightIRSensor;
    this->backLeftIRSensor = backLeftIRSensor;
    this->backRightIRSensor = backRightIRSensor;
    EnemyPosition = Position::MIDDLE_FRONT;
}

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
    int backLeft = backLeftIRSensor->getValue();
    int backRight = backRightIRSensor->getValue();
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