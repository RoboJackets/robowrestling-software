#include "world_state.hpp"
#include <Arduino.h>
#include <math.h>

namespace {
constexpr float MIN_TRACKED_SIGNAL = 0.22f;
constexpr float STRONG_CENTER_SIGNAL = 0.48f;
constexpr float FAR_FRONT_SIGNAL = 0.22f;
constexpr float OUTER_FLAG_SIGNAL = 0.34f;
constexpr float OUTER_SIDE_SIGNAL = 0.44f;
constexpr float INNER_SIDE_SIGNAL = 0.28f;
constexpr float CENTERED_BALANCE = 0.45f;
constexpr float MID_BALANCE = 0.25f;
constexpr float SIDE_BALANCE = 1.05f;
constexpr int ENEMY_HOLD_FRAMES = 10;
}

world_state::world_state(int* lineSensors, int* ir_sensors) {
    this->lineSensors = lineSensors;
    this -> ir_sensors = ir_sensors;
}

// void world_state::clean_sensors() {
//     for (int i = 0; i < 5; i++) {
//         if (ir_sensors[i] == 1) {
//             ir_sensors[i] = 0;
//             concurrency[i]++;
//         }
//         else {
//             concurrency[i] = 0;
//         }
//         if (concurrency[i] >= 10) {
//             ir_sensors[i] = 1;
//         }
//     }
// }

float* world_state::get_sensors_avg() {
    for (int i = 0; i < 5; i++) { //changed to 5 for 5 sensors
        avgs[i] += static_cast<float>(ir_sensors[i]) / static_cast<float>(buffer_size);
        avgs[i] -= rolling_avgs[i][head] / static_cast<float>(buffer_size);
        rolling_avgs[i][head] = ir_sensors[i];
    }

    head++;
    if (head >= buffer_size) {
        head = 0;
    }

    return avgs;
}

float world_state::totalSignal() const {
    float total = 0.0f;
    for (int i = 0; i < 5; i++) {
        total += avgs[i];
    }
    return total;
}

EnemyPosition world_state::classifyObservedEnemy() const {
    const float leftOuter = avgs[0];
    const float leftInner = avgs[1];
    const float center = avgs[2];
    const float rightInner = avgs[3];
    const float rightOuter = avgs[4];
    const float total = totalSignal();

    if (total < MIN_TRACKED_SIGNAL) {
        return NONE;
    }

    const float weightedBalance =
        ((-2.0f * leftOuter) - leftInner + rightInner + (2.0f * rightOuter)) / total;

    if (center >= STRONG_CENTER_SIGNAL) {
        if (leftOuter >= OUTER_FLAG_SIGNAL && leftOuter > rightOuter + 0.08f) {
            return FLAG_LEFT;
        }
        if (rightOuter >= OUTER_FLAG_SIGNAL && rightOuter > leftOuter + 0.08f) {
            return FLAG_RIGHT;
        }
        if (fabsf(weightedBalance) <= CENTERED_BALANCE) {
            return FRONT;
        }
    }

    if (weightedBalance <= -SIDE_BALANCE || leftOuter >= OUTER_SIDE_SIGNAL) {
        return LEFT;
    }
    if (weightedBalance >= SIDE_BALANCE || rightOuter >= OUTER_SIDE_SIGNAL) {
        return RIGHT;
    }

    if (weightedBalance < -MID_BALANCE || (leftInner >= INNER_SIDE_SIGNAL && leftInner > rightInner + 0.06f)) {
        return MIDLEFT;
    }
    if (weightedBalance > MID_BALANCE || (rightInner >= INNER_SIDE_SIGNAL && rightInner > leftInner + 0.06f)) {
        return MIDRIGHT;
    }

    if (center >= FAR_FRONT_SIGNAL) {
        return FARFRONT;
    }

    return NONE;
}

EnemyPosition world_state::enemy_pos() {
    EnemyPosition observedEnemy = classifyObservedEnemy();

    if (observedEnemy != NONE) {
        trackedEnemy = observedEnemy;
        lostEnemyFrames = 0;
        return trackedEnemy;
    }

    if (trackedEnemy != NONE && lostEnemyFrames < ENEMY_HOLD_FRAMES) {
        lostEnemyFrames++;
        return trackedEnemy;
    }

    trackedEnemy = NONE;
    lostEnemyFrames = 0;
    return NONE;
}

LinePosition world_state::line_check() {
    // UPDATED FOR DIGITAL SENSORS
    // LOW (0) means it sees the white line.
    bool left = (lineSensors[0] == LOW);
    bool right = (lineSensors[1] == LOW);

    if (left && right) return CENTER_LINE;
    if (left && !right) return LEFT_LINE;
    if (!left && right) return RIGHT_LINE;
    return OFF_LINE;
}
