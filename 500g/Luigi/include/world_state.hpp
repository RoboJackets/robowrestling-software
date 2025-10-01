#ifndef WORLD_STATE_H
#define WORLD_STATE_H
#include <vector>

class world_state {
    private:
        static const int buffer_size = 500;
        int* ir_sensors;
        int concurrency[3];
        long time;
        float rolling_avgs[3][buffer_size] = {0};
        float avgs[3] = {0};
        int head = 0;
    public:
        world_state(int* sensors);
        void clean_sensors();
        float* get_sensors_avg();
};

#endif