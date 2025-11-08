#include <Arduino.h>

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
private:
    unsigned long start_time;     // Time when timer started (millis)
    unsigned long duration_ms;    // Duration in milliseconds
    bool runningProcess;          // True if timer is active

public:
    Timer();                      // Default constructor
    Timer(unsigned long initial_time); // Optional constructor for consistency

    void begin();                 // Initialize timer (reset)
    void startTimer(unsigned long duration_ms); // Start a timer for N milliseconds
    void updateTime();            // Update state (call once per loop)
    bool getRunningProcess();     // Check if timer is active
    unsigned long getDuration(); // Remaining time in milliseconds
};

#endif // TIMER_HPP
