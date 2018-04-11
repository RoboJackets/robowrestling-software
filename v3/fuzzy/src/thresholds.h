// Thresholds for ToF sensors and Car ESCs

// Basic rule: 

// Raw Input: Distances
// max is 1250, seems like output of ToF is pretty much millimeters
// range: 0 to 1250
// low = far, high = close

int high1 = 0;
int high2 = 140;
int high3 = 280;
int high4 = 420;

int med1 = 430;
int med2 = 570;
int med3 = 710;
int med4 = 850;

int low1 = 860;
int low2 = 1000;
int low3 = 1140;
int low4 = 8192;

// Defuzzified Output: Velocities (translated into ESC PPM Values in loop)
// 		Test 1: Can this library output 1 of 5 states?
// 		Test 2: Can it output a single speed?
// 		Test 3: Can it output 2 ESC PPM values?

// 			Current: Test 1

// Turning timers

// 		Consult with Andrew

// Accelerometer collision threshold

// 		Consult with Mason