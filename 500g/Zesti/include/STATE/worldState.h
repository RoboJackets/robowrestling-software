#ifndef WORLD_STATE_H
#define WORLD_STATE_H
#include "Zesti/include/SENSOR/lineSensor.h"
#include "Zesti/include/SENSOR/irSensor.h"
#include <array>

class WorldState {
private:
    static const int NUM_READINGS = 10;

    std::array<int, NUM_READINGS> leftLineSensorReadings;
    std::array<int, NUM_READINGS> rightLineSensorReadings;
    int currentIndex;

    LineSensor leftLineSensor;
    LineSensor rightLineSensor;
public:

    WorldState();

    bool isLeftOnBlack();
    bool isRightOnBlack();
    bool isBothOnBlack();

    void updateSensors();

    int getEnemyPosition();
};

#endif