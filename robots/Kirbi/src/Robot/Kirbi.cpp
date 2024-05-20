#include "Robot/Kirbi.h"

Kirbi::Kirbi() {
    // This is just basic setup
    // The numbers in SerialX.begin() are the
    // baud rates (the rate at which data is sent)

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
    // We were planning to have more lidars...
    // Didn't work out...
    // Refactoring it to only be 2 would be a bit of work,
    // will do later

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

    _state.enabled = startModule->isActive();

    /*
        Line detection logic
        floorReading is what Kirbi determined to be the value of the floor to be
        during startup
        LINE_THRESHOLD is the threshold value of what to consider as a line

        This basically says "if either of the line sensors are reading something other than the floor,
        then we're probably reading a line (at the bounds of the dohyo)"

        The line sensors return some numeric value (depending on what they're looking at)
        and there's no easy way to just *know* what they're looking at based on that value
        - floorReading helps with this because floorReading tells us what the value of the floor is
        (determined in SampleFloor)
        - abs(GetDetection() - floorReading) tells us what the difference between what we're reading
        and the floor is
            - Low difference == probably looking at the floor;
            high difference == probably NOT looking at the floor (at a line)
            - abs is used because we might get a negative difference
        - LINE_THRESHOLD defines the amount of difference that's considered a line. For example, if
        LINE_THRESHOLD is 200, then the currently-read value and the floor's value have to differ by
        more than 200 to be considered a line
    */
    if (abs(lineSensor1->GetDetection() - floorReading) > LINE_THRESHOLD || abs(lineSensor2->GetDetection() - floorReading) > LINE_THRESHOLD) {
        _state.atBounds = true;
    } else {
        _state.atBounds = false;
    }
}

/*
    Determines the numeric value of the floor read by the line sensors.

    Ideally, both line sensors start over black, so when this function runs,
    we learn the numeric value of black. Therefore, when the line sensors
    read something OTHER than black, we can tell (see line detection logic in UpdateState).

    This function polls the line sensors 25 times, averages the values, and then averages
    all of the samples taken at the end. This should get us a pretty good idea of
    what black looks like.
*/
void Kirbi::SampleFloor() {
    unsigned int timestamp = millis();
    // uncomment one line and comment the other out
    // to select behavior
    while (millis() - timestamp < 5000) { //5 second delay
    //for (int i = 0; i < 25; i++) { //no 5 second delay
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
