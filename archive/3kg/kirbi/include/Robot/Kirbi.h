#ifndef KIRBI_H
#define KIRBI_H

#include <Arduino.h>
#include <memory>

#include "Robot/Robot.h"
#include "TFMini/TFMini.h"
#include "Sensors/LineSensor.h"
#include "Sensors/StartModule.h"
#include "MotorController.h"


constexpr int LINE_THRESHOLD = 100;

class Kirbi : public Robot {
private:
    TFMini* rightDist;
    TFMini* frontDist;
    TFMini* frontDist2;
    TFMini* leftDist;

    LineSensor* lineSensor1;
    LineSensor* lineSensor2;
    MotorController* motorController;
    std::unique_ptr<StartModule> startModule;

    int floorReading = 0;
    int samples = 0;

public:
    Kirbi();
    void UpdateState() override;
    void SampleFloor();
    MotorController* GetMotorController();
};

#endif
