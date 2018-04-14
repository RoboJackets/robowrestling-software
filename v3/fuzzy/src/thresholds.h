// Constant threshold values used

// Raw Input: Distances
	// max is 1250, seems like output of ToF is pretty much millimeters
	// range: 0 to 1250
	// low = far, high = close
const int high1 = 0;
const int high2 = 140;
const int high3 = 280;
const int high4 = 420;

const int med1 = 430;
const int med2 = 570;
const int med3 = 710;
const int med4 = 850;

const int low1 = 860;
const int low2 = 1000;
const int low3 = 1140;
const int low4 = 8192;

// Line sensor thresholds
const int maxS = 50;			// max fwd
const int maxR = 75;			// max rev

const int nudge = 750;
const int degrees180 = 1725; 	// turn 180 degrees

// Accelerometer collision threshold

// 		Consult with Mason