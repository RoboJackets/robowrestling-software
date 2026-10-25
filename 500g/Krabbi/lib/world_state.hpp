#ifndef WORLD_STATE_H
#define WORLD_STATE_H
#include "enums.hpp"

class world_state {
    private:
        static const int buffer_size = 18;
        int* ir_sensors;
        int* lineSensors;
        int concurrency[5];
        long time;
        float rolling_avgs[5][buffer_size] = {0};
        float avgs[5] = {0};
        int head = 0;
        EnemyPosition trackedEnemy = NONE;
        int lostEnemyFrames = 0;

        float totalSignal() const;
        EnemyPosition classifyObservedEnemy() const;
    public:
        world_state(int* line_sensors, int* ir_sensors);
        void clean_sensors();
        float* get_sensors_avg();
        EnemyPosition enemy_pos();
        LinePosition line_check();
};

#endif
