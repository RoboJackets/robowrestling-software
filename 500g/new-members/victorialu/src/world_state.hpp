#ifndef WORLD_STATE_H
#define WORLD_STATE_H

enum line_states {
    
}; //4 using line sensors black white

enum enemy_states {

}; //8? using ir sensors

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