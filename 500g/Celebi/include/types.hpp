#ifndef TYPES
#define TYPES

// #define PROFILING

struct start_info {
	uint8_t powers[8];
	uint16_t lengths[8];
};


#ifdef PROFILING
struct stats {
	int cycle_count = 0;
	unsigned long program_start = 0;
	unsigned long first_movement = 0;
	unsigned long program_end = 0;
	unsigned long poll_sensors = 0;
	unsigned long update_motors = 0;
	unsigned long update_state = 0;
};
struct algorithm_stats {
	unsigned long attack_pattern_time = 0;
    unsigned long draw_circle_time = 0;
    unsigned long attack_forward_time = 0;
    unsigned long turn_towards_time = 0;
	unsigned long process_sensors_time = 0;
};
#endif
#endif