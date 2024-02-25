#include "Robot/Kirbi.h"

Kirbi::Kirbi() {
    Serial1.begin(115200);
    Serial2.begin(115200);
    Serial3.begin(115200);
    Serial4.begin(115200);
    Serial5.begin(9600);

    startModule = std::make_unique<StartModule>(14);
    motorController = new MotorController(&Serial5);
    leftDist = new TFMini(&Serial3);
    rightDist =  new TFMini(&Serial2);
    lineSensor1 = new LineSensor(A9);
    lineSensor2 = new LineSensor(A16);

    _sensors.push_back(lineSensor1);
    _sensors.push_back(lineSensor2);
    _sensors.push_back(leftDist);
    _sensors.push_back(rightDist);

}

void Kirbi::UpdateState() {
    _state.lidars[0] = 0xFFFF;
    _state.lidars[1] = 0xFFFF;
    _state.lidars[2] = leftDist->GetDistance();
    _state.lidars[3] = rightDist->GetDistance();
    _state.lidars[4] = 0xFFFF;
    _state.lidars[5] = 0xFFFF;

    if (_state.lidars[2] == 0) {
        _state.lidars[2] = 0xFFFF;
    }


    if (_state.lidars[3] == 0) {
        _state.lidars[3] = 0xFFFF;
    }

    //Serial.printf("DIST | Left: %d, Right: %d \n", leftDist->GetDistance(),rightDist->GetDistance());
    //Serial.printf("DECT | Left: %d, Right: %d \n", lineSensor1->GetDetection(),lineSensor2->GetDetection());
    _state.enabled = startModule->isActive();


    if (abs(lineSensor1->GetDetection() - floorReading) > LINE_THRESHOLD || abs(lineSensor2->GetDetection() - floorReading) > LINE_THRESHOLD) {
        _state.atBounds = true;
    } else {
        _state.atBounds = false;
    }
}

void Kirbi::SampleFloor() {
    unsigned int timestamp = millis();
    //while (millis() - timestamp < 5000) {
    for (int i = 0; i < 25; i++) {
        lineSensor1->Poll();
        lineSensor2->Poll();
        int leftFloor = lineSensor1->GetDetection();
        int rightFloor = lineSensor2->GetDetection();

        int avg = (leftFloor + rightFloor) / 2;
        floorReading += avg;
        samples++;
    }

    floorReading = (floorReading / samples);
}

MotorController* Kirbi::GetMotorController() {
    return motorController;
}
