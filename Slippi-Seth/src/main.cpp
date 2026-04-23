/**
 * Celebi's main
 */


// #define USE_DEBUG
#define USE_STARTMOD

// imports

#include <Arduino.h>

#include "robot/algorithms.hpp"
#include "robot/robot_actions.hpp"

#include "world/world_state.hpp"
#include "world/timer.hpp"

#include "types.hpp"
#include "const.hpp"

// pinouts
#define Leftline A0
#define Rightline A4
#define Switch0 A1
#define Switch1 A2
#define Switch2 A3

#define Rdist 1
#define RMIDdist 2
#define CENTdist 4
#define LMIDdist 7
#define Ldist 12
#define StartMod 13
#define StartButton 8

#define RmotorPos 5
#define RmotorNeg 6
#define LmotorPos 10
#define LmotorNeg 9

// define motor array
int16_t motors[2] = {0,0};

// define sensor arrays
bool line_sensors[2] = {0,0};
bool ir_sensors[5] = {0,0,0,0,0};
uint8_t strategy = 0;

// set up algorithms class
algorithms* algorithm;

//set up robot actions
robot_actions* robot;

//set up world state
world_state* world;

timer *draw_timer;
timer *match_start_timer;

#ifdef PROFILING
stats profiling_stats;
algorithm_stats algo_stats;
#endif

// define functions
void updateMotors();
void pollSensors();
void updateState();
void brake();
void debug();
void update_stats();

void setup() {
	// define pinmodes
	pinMode(LmotorNeg, OUTPUT);
	pinMode(LmotorPos, OUTPUT);
	pinMode(RmotorNeg, OUTPUT);
	pinMode(RmotorPos, OUTPUT);
	pinMode(Switch0, INPUT_PULLUP);
	pinMode(Switch1, INPUT_PULLUP);
	pinMode(Switch2, INPUT_PULLUP);
	pinMode(Leftline, INPUT);
	pinMode(Rightline, INPUT);
	pinMode(Ldist, INPUT);
	pinMode(LMIDdist, INPUT);
	pinMode(CENTdist, INPUT);
	pinMode(RMIDdist, INPUT);
	pinMode(Rdist, INPUT);
	pinMode(StartMod, INPUT);
	pinMode(StartButton, INPUT);

	strategy = (!digitalRead(Switch2)) + (!digitalRead(Switch1) << 1) + (!digitalRead(Switch0) << 2);
	
	//initialize timer
	draw_timer = new timer(millis());
	match_start_timer = new timer(millis());

	//initialize world state
	world = new world_state(line_sensors, ir_sensors);

	//initialize robot actions
	robot = new robot_actions(motors);

	//initialize strategy
	algorithm = new algorithms(robot, world, &strategy, draw_timer, match_start_timer);

#ifdef USE_DEBUG
	Serial.begin(9600);
	Serial.println("we are running");
#endif

#ifdef PROFILING
	algorithm->add_stats(&algo_stats);
	Serial.begin(9600);
#endif

	draw_timer->set_action_timer(10);
	// wait for start signal
#ifdef USE_STARTMOD
	while (!digitalRead(StartMod)) {
		strategy = (!digitalRead(Switch2)) + (!digitalRead(Switch1) << 1) + (!digitalRead(Switch0) << 2);
		// if (strategy != 0) {
		// 	if (strategy <= 3) {
        //     	robot->drive_custom(start_data.powers[strategy], max_speed, 1, 1);
        // 	} else if (strategy == 4) {
        //     	robot->drive_forward(start_data.powers[strategy]);
        // 	} else {
        //     	robot->drive_custom(max_speed, start_data.powers[strategy], 1, 1);
        // 	}
		// }
#ifdef PROFILING
		Serial.begin(9600);
		profiling_stats.program_start = micros();
#endif 
	}
#endif

	// while (!digitalRead(StartButton)) {
	//	;
	// }
// 	if (strategy != 0) {
// 		analogWrite(RmotorNeg, 0);
// 		analogWrite(RmotorPos, motors[1]);
// 		analogWrite(LmotorNeg, 0);
// 		analogWrite(LmotorPos, motors[0]);
// #ifdef PROFILING
// 		profiling_stats.first_movement = micros();
// #endif
// 	}

	match_start_timer->update_time(millis());
	match_start_timer->set_action_timer(150);
}

void loop() {
	pollSensors();
	updateState();
	updateMotors();

	// listen for stop signal
#ifdef USE_STARTMOD
	if (!digitalRead(StartMod)) {
		while(true) {
		brake();
		}
	}
#endif

#ifdef USE_DEBUG
	debug();
#endif

#ifdef PROFILING
	update_stats();
#endif

}

void pollSensors() {
#ifdef PROFILING
	long start_poll = micros();
#endif
	//read line sensors
	int left = analogRead(Leftline);
	int right = analogRead(Rightline);

	//if both are black, bin = 0
	//if just right is black, bin = 1
	//if just left is black, bin = 2
	//if both are white, bin = 3

	line_sensors[0] = left < 100 ? 1 : 0;
	line_sensors[1] = right < 100 ? 1 : 0;


	//read ir sensors
	ir_sensors[0] = digitalRead(Ldist);
	ir_sensors[1] = digitalRead(LMIDdist);
	ir_sensors[2] = digitalRead(CENTdist);
	ir_sensors[3] = digitalRead(RMIDdist);
	ir_sensors[4] = digitalRead(Rdist);


	draw_timer->update_time(millis());
	match_start_timer->update_time(millis());

	strategy = (!digitalRead(Switch2)) + (!digitalRead(Switch1) << 1) + (!digitalRead(Switch0) << 2);
#ifdef PROFILING
	profiling_stats.poll_sensors += micros() - start_poll;
#endif
}

void updateState() {
#ifdef PROFILING
	int start_update = micros();
#endif
	algorithm->match_strategy();
	// algorithm->test();
#ifdef PROFILING
	profiling_stats.update_state += micros() - start_update;
#endif
}

/**
 * Implemented for Celebi's motordrivers
 * motordriver takes positive and negative power
 * Max speed is 255
 */ 
void updateMotors() {
#ifdef PROFILING
	int start_motor_update = micros();
#endif
	if (motors[0] > 0) {	// if direction is forward
		analogWrite(LmotorPos, motors[0]);
		analogWrite(LmotorNeg, 0);
	} else {	 // if direction is backward
		analogWrite(LmotorPos, 0);
		analogWrite(LmotorNeg, abs(motors[0]));
	}

	if (motors[1] > 0) {	// if direction is forward
		analogWrite(RmotorPos, motors[1]);
		analogWrite(RmotorNeg, 0);
	} else {				// if direction is back
		analogWrite(RmotorPos, 0);
		analogWrite(RmotorNeg, abs(motors[1]));
	}
#ifdef PROFILING
	profiling_stats.update_motors = micros() - start_motor_update;
#endif
}


void brake() {
	robot->brake();
	updateMotors();
}

#ifdef PROFILING
void update_stats() {
	if (profiling_stats.cycle_count++ == 10000) {
		profiling_stats.program_end = micros();
		Serial.begin(9600);
		delay(500);
		if (strategy == 0) {
			profiling_stats.first_movement = 0;
		} else {
			profiling_stats.first_movement-= profiling_stats.program_start;
		}
		profiling_stats.poll_sensors /= 1000;
		profiling_stats.update_motors /= 1000;
		profiling_stats.update_state /= 1000;
		Serial.println("Total program time: " + String(profiling_stats.program_end - profiling_stats.program_start));
		Serial.println("Start to first motor write: " + String(profiling_stats.first_movement));
		Serial.println("Time spent in poll sensors: " + String(profiling_stats.poll_sensors));
		Serial.println("Time spent in state update: " + String(profiling_stats.update_state));
		Serial.println("\tTime spent in attack pattern (almost all) " + String(algo_stats.attack_pattern_time));
		Serial.println("\tTime spent in draw circle: " + String(algo_stats.draw_circle_time));
		Serial.println("\tTime spend in attack forward: " + String(algo_stats.attack_forward_time));
		Serial.println("\tTime spent in turn towards: " + String(algo_stats.turn_towards_time));
		Serial.println("\tTime spent updating world: " + String(algo_stats.process_sensors_time));
		Serial.println("Time spent in motor update: " + String(profiling_stats.update_motors));
		
		
		Serial.println(String(profiling_stats.program_end - profiling_stats.program_start) + ", " + 
						String(profiling_stats.first_movement) + ", " + String(profiling_stats.poll_sensors) + ", "
						+ String(profiling_stats.update_state) + ", " + String(profiling_stats.update_motors));
		
        // (String("Time spent in ") + 
        // String(__FUNCTION__) + 
        // String("()")).c_str())
		while(1) {
			;
		}
	} else {
		// Serial.println(profiling_stats.cycle_count);
	}
}
#endif

#ifdef USE_DEBUG
void debug() {
	if (millis() % 100 != 0) {
	return;
	}
	// Serial.println("\n\n*****************");
	Serial.println(String(strategy) + ", " + String(index));
	
	// Start Modules
	// Serial.print("start mod: ");
	// Serial.println(digitalRead(StartMod));
	
	//Timer debugging

	// Serial.print("action timer has gone off: ");
	// Serial.println(thymer->check_action_time());
	// Serial.print("time since match start: ");
	// Serial.println(thymer->check_match_time());
	// Serial.print("millies: ");
	// Serial.println(millis());
	// Serial.print("action timer started at: ");
	// Serial.println(attack_timer->get_action_start());
	// Serial.print("current time from timer: ");
	// Serial.print("timer status: ");
	// Serial.println(match_start_timer->get_timer_state());
	
	
	// line sensors
	
	// Serial.println(line_sensors[0]);
	// Serial.println(line_sensors[1]);


	//distance sensors

	// Serial.print("distance left: ");
	// Serial.println(ir_sensors[0]);

	// Serial.print("distance mid left: ");
	// Serial.println(ir_sensors[1]);

	// Serial.print("distance mid: ");
	// Serial.println(ir_sensors[2]);

	// Serial.print("distance mid right: ");
	// Serial.println(ir_sensors[3]);

	// Serial.print("distance right: ");
	// Serial.println(ir_sensors[4]);


	// motors

	// Serial.println("motors:");

	// Serial.print("left motor: ");
	// Serial.println(motors[0]);

	// Serial.print("right motor: ");
	// Serial.println(motors[1]);


	//state
	// Serial.println(world ->enemy_pos());
	
	
	// Serial.println("*****************");
}
#endif