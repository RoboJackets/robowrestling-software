#include "world_state.hpp"
#include <Arduino.h>

world_state::world_state(int* lineSensors, int* ir_sensors) {
    this->lineSensors = lineSensors;
    this->ir_sensors = ir_sensors;
}

// OPTIMIZED: Uses an O(1) running sum to drastically speed up loop times.
float* world_state::get_sensors_avg() {
    static int sums[5] = {0}; 
    
    // Move head forward
    head = (head + 1) % buffer_size;
    
    for (int i = 0; i < 5; i++) { 
        // Subtract the oldest value from our running total
        sums[i] -= rolling_avgs[i][head];
        
        // Overwrite the oldest value with the new reading
        rolling_avgs[i][head] = ir_sensors[i];
        
        // Add the new reading to our running total
        sums[i] += ir_sensors[i];
        
        // Calculate the average directly from the running sum
        avgs[i] = static_cast<float>(sums[i]) / buffer_size;
    }
    return avgs;
}

EnemyPosition world_state::enemy_pos() {
    // A center detection takes priority over side flags. Symmetric inner
    // detections indicate a centered target rather than an arbitrary left turn.
    if (avgs[2] >= 0.9) {
        bool left = (avgs[1] >= 0.9);
        bool right = (avgs[3] >= 0.9);
        if (left && !right) return FRONT_LEFT;
        if (right && !left) return FRONT_RIGHT;
        return FRONT;
    }

    // Extreme outside flags
    if (avgs[1] >= 0.9 && avgs[0] >= 0.9) return FLAG_LEFT;  
    if (avgs[3] >= 0.9 && avgs[4] >= 0.9) return FLAG_RIGHT;

    // Standard zones
    if (avgs[1] >= 0.9) return MIDLEFT;
    if (avgs[3] >= 0.9) return MIDRIGHT;
    if (avgs[0] >= 0.9) return LEFT;
    if (avgs[4] >= 0.9) return RIGHT;
    
    return NONE;
}

LinePosition world_state::line_check() {
    bool left = (lineSensors[0] == LOW);
    bool right = (lineSensors[1] == LOW);

    if (left && right) return CENTER_LINE;
    if (left && !right) return LEFT_LINE;
    if (!left && right) return RIGHT_LINE;
    return OFF_LINE;
}
