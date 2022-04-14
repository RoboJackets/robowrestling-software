#include <opening/timed_opening.h>
#include <iostream>

TimedOpening::TimedOpening() {
    start_time = std::chrono::system_clock::now();
}

// while the time passed has not exceeded the time limit, the robot will continue.
std::vector<int> TimedOpening::execute(SensorData input) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    int output[] = {20, 30};
    if (now.time_since_epoch() - start_time.time_since_epoch() <= time_limit) {
        return std::vector<int>(output, output + sizeof(output) / sizeof(int));
    }
    done = true;
    return std::vector<int>(output, output + sizeof(output) / sizeof(int));
}
