#include "worldState.h"

worldState::worldState(worldState::robotSensors sensors){
    this->frontLineSensor = sensors.frontLineSensor;
    this->backLineSensor = sensors.backLineSensor;
    this->frontLeftIRSensor = sensors.frontLeftIRSensor;
    this->frontRightIRSensor = sensors.frontRightIRSensor;
    this->backLeftIRSensor = sensors.backLeftIRSensor;
    this->backRightIRSensor = sensors.backRightIRSensor;
    EnemyPosition = Position::MIDDLE_FRONT;
    lastEnemyPosition = Position::MIDDLE_FRONT;
}

Position worldState::getEnemyPosition(){
    int frontLeft = frontLeftIRSensor->getValue();
    int frontRight = frontRightIRSensor->getValue();
    int backLeft = backLeftIRSensor->getValue();
    int backRight = backRightIRSensor->getValue();

    

    if (frontLeft && frontRight) {
        EnemyPosition = Position::MIDDLE_FRONT;
        lastEnemyPosition = EnemyPosition;
    } else if (frontLeft) {
        EnemyPosition = Position::FRONT_RIGHT;
        lastEnemyPosition = EnemyPosition;
    } else if (frontRight) {
        EnemyPosition = Position::FRONT_LEFT;
        lastEnemyPosition = EnemyPosition;
    } else if (backLeft && backRight) {
        EnemyPosition = Position::MIDDLE_BACK;
        lastEnemyPosition = EnemyPosition;
    } else if (backLeft) {
        EnemyPosition = Position::BACK_RIGHT;
        lastEnemyPosition = EnemyPosition;
    } else if (backRight) {
        EnemyPosition = Position::BACK_LEFT;
        lastEnemyPosition = EnemyPosition;
    } else {
        
        EnemyPosition = Position::NONE;
    }
    return EnemyPosition;
}

Position worldState::getLastEnemyPosition(){
    return lastEnemyPosition;
}
void worldState::setLastEnemyPosition(Position position){
    lastEnemyPosition = position;
}

Position worldState::getPosition(){
    int frontLine = frontLineSensor->getValue();
    int backLine = backLineSensor->getValue();

    if (frontLine) {
        return Position::ON_LINE_FRONT;
    } else if (backLine) {
        return Position::ON_LINE_BACK;
    } else {
        return Position::NONE;
    }
}