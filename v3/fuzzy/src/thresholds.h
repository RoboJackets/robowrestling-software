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

// Output: Speeds
	// For turns, the inner wheel is slower than the outer wheel
const int v_small_slow = 60;
const int v_small_fast = 80;

const int v_full_slow = 50;
const int v_full_fast = 90;

const int v_center = 70;

// Line sensor thresholds
const int line_fwd = 75;		// max fwd

const int line_rev = 75;		// max rev
const int nudge = 750;			// duration of reverse maneuver (ms)

const int line_180 = 75;
const int degrees180 = 1500; 	// duration of 180 deg turn (ms)

const int degrees45 = 350;

// Accelerometer collision threshold

// 		Consult with Mason, TBD
