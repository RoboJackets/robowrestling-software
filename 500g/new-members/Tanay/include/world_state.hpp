#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP


enum class line_states {
    UNSAFE,
    LEFT,
    RIGHT,
    SAFE
};

enum class enemy_states {
    FRONT,
    LEFT,
    RIGHT,
    UNKNOWN
};

class world_state {
    public:
        // Constructor
        world_state(int* line_sensors, int* ir_sensors);

        // Existing functionality
        void clean_sensors();

        // New UML-based methods
        line_states line_check();   // use line_sensors to decide robot pos
        enemy_states enemy_pos();   // use ir_sensors to decide enemy pos

    private:
        // Old stuff
        int* ir_sensors;       // pointer to IR sensors
        int concurrency[3];    // debounce/filter array

        // New stuff
        int* line_sensors;     // pointer to line sensors
};

#endif // WORLD_STATE_HPP
