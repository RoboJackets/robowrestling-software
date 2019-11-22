#include "gucci.h"
#include "VL53L0X.h"

x_accel = new CircularArray<double>(8);
y_accel = new CircularArray<double>(8);
distances = new CircularArray<int[6]>(8);

enum State {
    SEARCH_LEFT,
    SEARCH_RIGHT,
    ADJUST_LEFT,
    ADJUST_RIGHT,
    SLAMMY_WHAMMY,
    PANIC_HIT,
    PANIC_FIRE,
    WAIT_FOR_START,
    STARTUP
};


State state_machine(State lastState) {
    curr_time = micros();
    get_distances();
    get_current();
    if (percent_overloaded_left > 1 || percent_overloaded_right > 1) {
        return PANIC_FIRE;
    }
    if (curr_time - prev_time > check_accel) {
        prev_time_accel = millis();
        get_accel();
    }
    int[] curr_distances = distances.getFront();

    if (curr_distances[2] <= MAX_DIST) { // bot on left
        if (curr_distances[3] <= MAX_DIST) { // bot on right
            if (curr_distances[1] == 0 && curr_distances[4] == 0) {
              //
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return SLAMMY_WHAMMY; //temp but kinda what we want
            } else if (curr_distances[1] == 1 && curr_distances[4] == 0) {
              //45 left
                left_turn_ratio = 1;
                right_turn_ratio = 0.9;
                return ADJUST_LEFT;
            } else if (curr_distances[1] == 0 && curr_distances[4] == 1) {
              // 45 right
                left_turn_ratio = 0.9;
                right_turn_ratio = 1;
                return ADJUST_RIGHT;
            } else {
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return SLAMMY_WHAMMY; //either we're seeing them on all 4 middle sensors or something weird is happening
            }
        } else { // no bot on right
            if (curr_distances[0] == 0 && curr_distances[1] == 1) {
              // no left, on 45 left only
                left_turn_ratio = 1;
                right_turn_ratio = ?;
                return ADJUST_LEFT;
            } else if (curr_distances[1] == 1) {
              // on left and 45 left
                left_turn_ratio = 1;
                right_turn_ratio = ?;
                return ADJUST_LEFT;
            } else {
              //
                left_turn_ratio = 1;
                right_turn_ratio = ?;
                return ADJUST_LEFT;
            }
        }
    } else if (curr_distances[3] <= MAX_DIST) { // bot on right
        if (curr_distances[5] == 0 && curr_distances[4] == 1) {
            left_turn_ratio = ?;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else if (curr_distances[4] == 1) {
            left_turn_ratio = ?;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else {
            left_turn_ratio = ?;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        }
    } else if (curr_distances[1] == 1) { // no bot on right and bot left 45
        if (curr_distances[0] == 1) {
            left_turn_ratio = 1;
            right_turn_ratio = ?;
            return ADJUST_LEFT;
        } else {
            left_turn_ratio = 1;
            right_turn_ratio = ?;
            return ADJUST_LEFT;
        }
    } else if (curr_distances[4] == 1) {
        if (curr_distances[5] == 1) {
            left_turn_ratio = ?;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else {
            left_turn_ratio = ?;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        }
    } else if (curr_distances[0] == 1) {
        return SEARCH_LEFT;
    } else if (curr_distances[5] == 1) {
        return SEARCH_RIGHT;
    } else if (lastState == WAIT_FOR_START) {
        return STARTUP;
    }

}

void drive(int left, int right, bool left_reverse, bool right_reverse) {
    left = left*left_multi*left_turn_ratio;
    right = right*right_multi*right_turn_ratio;
    ESC_SERIAL.write(ESC_ADDRESS);
    ESC_SERIAL.write(left_reverse);
    ESC_SERIAL.write(left);
    ESC_SERIAL.write((ESC_ADDRESS+left_reverse+left)&ESC_CHECKSUM);
    ESC_SERIAL.write(ESC_ADDRESS);
    ESC_SERIAL.write(right_reverse);
    ESC_SERIAL.write(right);
    ESC_SERIAL.write((ESC_ADDRESS+right_reverse+right)&ESC_CHECKSUM);
}

/**
 * INTERRUPT METHODS
**/
void do_line_action_left() {
    //TODO: implement
    drive(x, y, true, true);
}
void do_line_action_right() {
    //TODO: implement
    drive(y, x, true, true);
}

void increment_encoder_right() {
    right_encoder++;
}

void increment_encoder_left() {
    left_encoder++;
}

/**
 * Method for startup action
**/
void do_startup_action() {
    //TODO: implement
}

/**
 * SETUP METHODS
**/
 void setup_imu() {
    pinMode(9, OUTPUT);
    digitalWrite(9, LOW);
    Wire2.begin();
    Wire2.setSDA(8);
    Wire2.setSCL(7);
    icm.begin()
    icm.disableDataReadyInterrupt();
    icm.configAccel(ICM20948::ACCEL_RANGE_2G, ICM20948::ACCEL_DLPF_BANDWIDTH_6HZ);
    icm.configGyro(ICM20948::GYRO_RANGE_250DPS, ICM209480::GYRO_DLPF_BANDWIDTH_6HZ);
 }

 void setup_distance() {
    /* tof setup */
    
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(32, OUTPUT);

    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);

    Wire.setSpeed(CLOCK_SPEED_100KHZ);
    Wire.begin();
    Wire.setSDA(A15);
    Wire.setSCL(A14);

    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
    digitalWrite(32, HIGH);

    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);

    tof_left.init();
    tof_left.setAddress(0x31);
    tof_left.setTimeout(1000);
    digitalWrite(0, HIGH);
    tof_left_45.init();
    tof_left_45.setAddress(0x32);
    tof_left_45.setTimeout(1000);
    digitalWrite(1, HIGH);
    tof_left_center.init();
    tof_left_center.setAddress(0x33);
    tof_left_center.setTimeout(1000);
    digitalWrite(2, HIGH);
    tof_right_center.init();
    tof_right_center.setAddress(0x34);
    tof_right_center.setTimeout(1000);
    digitalWrite(30, HIGH);
    tof_right_45.init();
    tof_right_45.setAddress(0x35);
    tof_right_45.setTimeout(1000);
    digitalWrite(31, HIGH);
    tof_right.init();
    tof_right.setAddress(0x36);
    tof_right.setTimeout(1000);
    digitalWrite(32, HIGH);

    tof_left.startContinuous(10);
    tof_left_45.startContinuous(10);
    tof_left_center.startContinuous(10);
    tof_right_center.startContinuous(10);
    tof_right_45.startContinuous(10);
    tof_right.startContinuous(10);  
 }

 void setup_current() {
    pinMode(LEFT_CURRENT, INPUT);
    percent_overloaded = 0;
    check_current = 0;
 }

 void setup_motors(){
    left_multi = 1;
    right_multi = 1;
    left_turn_ratio = 1;
    right_turn_ratio = 1;
    ESC_SERIAL.begin(115200);
    
 }

/**
 * SENSOR READ METHODS
**/
void get_accel() {
    x_accel.add(icm.getAccelX_mss());
    y_accel.add(icm.getAccelY_mss());
}
void get_gyro() {
    //TODO: implement?
}
void get_distances() {
    int[] dist = int[6];
    dist[0] = tof_left.readRangeContinuousMillimeters();
    dist[1] = tof_left_45.readRangeContinuousMillimeters();
    dist[2] = tof_left_center.readRangeContinuousMillimeters();
    dist[3] = tof_right_center.readRangeContinuousMillimeters();
    dist[4] = tof_right_45.readRangeContinuousMillimeters();
    dist[5] = tof_right.readRangeContinuousMillimeters();
    distances.add(dist);
    return dist;
}
int read_lidar(Serial s) {
    byte[] bytes = byte[9];
    s.readBytes(bytes, 9);
    int dist_low = 0;
    while (dist_low < 9) {
        if (bytes[dist_low] == 0x89) {
            if (dist_low == 0) {
                if (bytes[8] == 0x89) {
                    return bytes[1] + (bytes[2] << 8);
                }
            } else if (dist_low == 7) {
                if (bytes[8] == 0x89) {
                    return bytes[0] + (bytes[1] << 8);
                }
            } else {
                if (bytes[++dist_low] == 0x89) {
                    return bytes[++dist_low] + (bytes[++dist_low] << 8);
                }
            }
        }
        dist_low++;
    }
    return read_lidar(s);
}
void get_current() {
    int time_at_current = curr_time - last_read_current;
    last_read_current = curr_time;
    int current = analogRead(LEFT_CURRENT)*voltage_to_current; //read in voltage then change to current using magic number
    total_currentxtime_left += time_at_current*current; //Keep track of current*time over the interval to average later
    int current = analogRead(RIGHT_CURRENT)*voltage_to_current;
    total_currentxtime_right += time_at_current*current;
    int time_since_check = curr_time - prev_time_current;
    if (time_since_check > check_overload) { //is it time to check the overload?
        prev_time_current = curr_time;
        current = total_currentxtime_left/(time_since_check);
        double k_left = current/precalc;
        total_currentxtime_left = 0;
        current = total_currentxtime_right/(time_since_check);
        double k_right = current/precalc;
        total_currentxtime_right = 0;
        if (k_left > 1) { //are we overloading?
            double k2 = pow(k_left, 2);
            double ton = tw * log(k2/(k2-1));
            percent_overloaded_left += time_since_check/ton; //add the time that we were overloading/time we can
                                                             //overload for at that at that amperage to our percent overloaded
        }
        if (k_right > 1) {
            double k2 = pow(k_right, 2);
            double ton = tw * log(k2/(k2-1));
            percent_overloaded_right += time_since_check/ton;
        }
    }


}

/**
 * OTHER
**/
void balance_motors() {
    if (left_encoder > right_encoder) {
        left_multi = right_encoder/left_encoder;
        right_multi = 1;
    } else {
        right_multi = left_encoder/right_encoder;
        left_multi = 1;
    }
}