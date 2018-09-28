#include <Particle.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

#include <thresholds.h>

#include <sensors.h>

#include <movement.h>

Servo LESC;
Servo RESC;

//Setting up servos
void ESC_init() {
    // Necessary for Servo objects
    LESC.attach(Lmotor);
    RESC.attach(Rmotor);
    // Write stop command
    LESC.writeMicroseconds(1500);
    RESC.writeMicroseconds(1500);
}

void stop() {
  	LESC.writeMicroseconds(1500);
  	RESC.writeMicroseconds(1500);
}

void move(int motor, int speed, int direction){
  // usage: x_ESC.writeMicroseconds(pwm)
  // pwm should between 1100 and 1800
  // 1100 for maximum reverse, 1800 for maximum forward
  // 30% throttle is 1500 +/- 300*0.3 = 1500 +/- 90

  int pwm = 1500;       // default is ESC stopped

  if(direction == 1) {  // forward
    pwm = 1500 + speed;
  } else {              // reverse
    pwm = 1500 - speed;
  }
  if(motor == 1) {      // RIGHT ESC
    RESC.writeMicroseconds(pwm);
  } else {              // LEFT ESC
    LESC.writeMicroseconds(pwm);
  }
}

//
void movement(int state) {
	// right now, there are only states 0, 1, and 10***
	if(state == 0) {			// move forward
  		L_command = line_fwd;
  		R_command = line_fwd;
  		L_dir = 1;
  		R_dir = 1;
      // Serial.println("Back triggered, moving forward");
<<<<<<< .merge_file_6wvTYL
	} else if (state == 2) {
=======
	} else if (state == 2) { //Should be 1?
>>>>>>> .merge_file_S6NY75
    if (cur - prevFlag < degrees45) {
      L_command = line_180;
      R_command = line_180;
      L_dir = 0;
      R_dir = 1;
    } else {
      // Serial.print("start done");
      start = false;
      prevFlagSet = false;
    }
  } else if (state == 10) {
	    if (cur - prevFlag < nudge) {			// go backwards a 'nudge'
	  		L_command = line_rev;
	  		R_command = line_rev;
	  		L_dir = 0;
	  		R_dir = 0;
        // Serial.println("Moving backwards a nudge");
	    }
	    else if (cur - prevFlag < degrees180) {	// turn cw 180
	  		L_command = line_180;
	  		R_command = line_180;
	  		R_dir = 0;
	  		L_dir = 1;
        // Serial.println("Turning 180");
	    }
	    else {									// reset line flags & detection flag
        FLflag = true;						// only when movement is FINISHED
        FRflag = true;
	      BLflag = true;
	      BRflag = true;
	      prevFlagSet = false;
        // Serial.println("FINISHED DEALING WITH THE LINE");
	    }
	    // moving = true;
	} else {					// stop
  		L_command = 0;
  		R_command = 0;
  		R_dir = 1;
  		L_dir = 1;
      // Serial.println("Stopped before death");
	}
}
