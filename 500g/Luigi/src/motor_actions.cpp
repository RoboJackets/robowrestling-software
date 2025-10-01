#include <Arduino.h>
#include "motor_actions.hpp"
#include <algorithm>

motor_actions::motor_actions(int* motors, int* sensors, timer* actionTimer) {
    this -> motors = motors;
    this -> ir_sensors = sensors;
    this -> actionTimer = actionTimer;
    actionTimer->start();
}

void motor_actions::drive_binary() {
    seeThing = true;
    for (int i = 0; i < 3; i++) {
        if (ir_sensors[i] == 0) {
            seeThing = false;
        }
    }
    if (seeThing) {
        if (!lastSawThing) {
            actionTimer->reset();
        }
        actionTimer->start();
        motors[0] = 80;
        motors[1] = std::min(80, static_cast<int>(40 + actionTimer->elapsedMilliseconds() / 25));

    }
    else {
        if (lastSawThing) {
            actionTimer->reset();
        }
        actionTimer->start();
        motors[0] = -80;
        motors[1] = std::min(80, static_cast<int>(40 + actionTimer->elapsedMilliseconds() / 25));
    }
    lastSawThing = seeThing;
}

void motor_actions::drive_avgs(float* avgs) {
    // the average sight value hovers around 0.3 when nothing is seen
    // so we map the range [0.3, 1.0] to [0.0, 1.0]
    float avg_sight = std::max(((avgs[0] + avgs[1] + avgs[2])/3.0-0.3)/0.7, 0.0);
    if (avg_sight < 0.1) {
        avg_sight = 0.0;
    }
    // swaps from turing to charging as the vision improves
    motors[0] = static_cast<int>(std::min(static_cast<float>(-75 + 250 * avg_sight), 150.0f));
    motors[1] = std::max(75, motors[0]);
}
