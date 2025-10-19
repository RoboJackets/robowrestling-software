#include <cstdint>
#ifndef TIMER_H
#define TIMER_H

// TODO: make timer have a parameter function call that gets called when ready as oppose to current implementation

class Timer {
  public:
    bool getReady();
    void setTimeInterval(uint32_t time);
    void setCurrentTime(uint32_t time);
    void setPreviousTime(uint32_t time);
  private:
    uint32_t currentTime = 0;
    uint32_t previousTime = 0;
    uint32_t timeInterval = 0;
};


#endif

