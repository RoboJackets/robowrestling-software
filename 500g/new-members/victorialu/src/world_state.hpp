#ifndef WORLD_STATE_H
#define WORLD_STATE_H

enum line_states {
    LINE_BOTH_WHITE,
    LINE_LEFT_WHITE,
    LINE_RIGHT_WHITE,
    LINE_BOTH_BLACK
}; //4 using line sensors black white

enum enemy_states {
    ENEMY_NONE,        
    ENEMY_LEFT,        
    ENEMY_CENTER,     
    ENEMY_RIGHT,     
    ENEMY_LEFT_CENTER, 
    ENEMY_CENTER_RIGHT,
    ENEMY_LEFT_RIGHT,
    ENEMY_ALL
}; //8 using ir sensors

class world_state {
    private:
        int* ir_sensors;
        int* line_sensors;
    public:
        world_state(int* ir, int* line);
        line_states line_check();
        enemy_states enemy_pos();
        void clean();
};

#endif