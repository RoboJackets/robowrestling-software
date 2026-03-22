#ifndef TIMER_HPP
#define TIMER_HPP

class timer {
public:
    void start();
    void stop();
    void reset();
    void setTarget(long target);
    bool isRunning();
    bool isFinished();
    long elapsedMilliseconds();
    timer(long* currentMillis);

private:
    long* currentMillis;
    long startMillis;
    long endMillis;
    long targetMillis;
    bool running;
};

#endif