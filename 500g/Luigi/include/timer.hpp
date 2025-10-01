#ifndef TIMER_HPP
#define TIMER_HPP

class timer {
public:
    void start();
    void stop();
    void reset();
    bool isRunning();
    long elapsedMilliseconds();
    timer(long* currentMillis);

private:
    long* currentMillis;
    long startMillis;
    long endMillis;
    bool running;
};

#endif