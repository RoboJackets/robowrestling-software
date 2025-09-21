#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class World_State {
public:


    World_State(int* lineSensors, int* irSensors);

    // LineState line_check();
    // EnemyState enemy_pos();
    void checkConcurrency();

    int* getMotors() {};
private:
    
    int* lineSensors;   // pointer to 2 line sensors
    int* irSensors;     // pointer to 3 IR sensors
    int concurrency[3];
};

#endif
