#ifndef WORLD_STATE_H
#define WORLD_STATE_H
#include <vector>
#include "enums.hpp"

class world_state {
    private:
        static const int buffer_size = 500;
        int* ir_sensors;
        int* lineSensors;
        int concurrency[3];
        long time;
        float rolling_avgs[3][buffer_size] = {0};
        float avgs[3] = {0};
        int head = 0;
    public:
        world_state(int* line_sensors, int* ir_sensors);
        void clean_sensors();
        float* get_sensors_avg();
        EnemyPosition enemy_pos();
        LinePosition line_check();
};

#endif