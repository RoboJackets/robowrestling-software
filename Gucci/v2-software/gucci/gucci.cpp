#include "gucci.h"

//x_accel = new CircularArray<double>(8);
//y_accel = new CircularArray<double>(8);
//distances = new CircularArray<int[6]>(8);

ICM20948 icm(Wire2, (uint8_t)0x68);

int dist[6];

/* distance sensors */
VL53L0X tof_left;
VL53L0X tof_left_45;
VL53L0X tof_left_center;
VL53L0X tof_right_center;
VL53L0X tof_right_45;
VL53L0X tof_right;

/* acceleration timing variables */
int curr_time;
int prev_time_accel;
int check_accel;

/* encoder counts */
int right_encoder;
int left_encoder;

double left_multi;
double right_multi;

double left_turn_ratio;
double right_turn_ratio;


/* Current sensing stuff */
double r1 = 2.3;
double r2 = 7.28;
double nominal_current = 4.12;
const double precalc = 2.01873; //nominal_current*(sqrt(r1/(r1+r2)))
const double tw = 42.2;
int total_currentxtime_left;
int total_currentxtime_right;
double percent_overloaded_left;
double percent_overloaded_right;
int prev_time_current; //for use with curr_time
int last_read_current;
int check_overload;
const double voltage_to_current = .01611328;


State state_machine(State lastState) {
    curr_time = micros();
    get_distances();
    get_current();
    if (percent_overloaded_left > 1 || percent_overloaded_right > 1) {
        return PANIC_FIRE;
    }
    if (curr_time - prev_time_accel > check_accel) {
        prev_time_accel = millis();
        get_accel();
    }
    int* curr_distances = dist;

    if (curr_distances[2] <= MAX_DIST) { // bot on left
        if (curr_distances[3] <= MAX_DIST) { // bot on right
            if (curr_distances[1] > MAX_DIST && curr_distances[4] > MAX_DIST) {
              //
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return SLAMMY_WHAMMY; //temp but kinda what we want
            } else if (curr_distances[1] < MAX_DIST && curr_distances[4] > MAX_DIST) {
              //45 left
                left_turn_ratio = 1;
                right_turn_ratio = 0.9;
                return ADJUST_LEFT;
            } else if (curr_distances[1] > MAX_DIST && curr_distances[4] < MAX_DIST) {
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
            if (curr_distances[0] > MAX_DIST && curr_distances[1] < MAX_DIST) {
              // no left, on 45 left only
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return ADJUST_LEFT;
            } else if (curr_distances[1] < MAX_DIST) {
              // on left and 45 left
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return ADJUST_LEFT;
            } else {
              //
                left_turn_ratio = 1;
                right_turn_ratio = 1;
                return ADJUST_LEFT;
            }
        }
    } else if (curr_distances[3] <= MAX_DIST) { // bot on right
        if (curr_distances[5] > MAX_DIST && curr_distances[4] < MAX_DIST) {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else if (curr_distances[4] < MAX_DIST) {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        }
    } else if (curr_distances[1] < MAX_DIST) { // no bot on right and bot left 45
        if (curr_distances[0] < MAX_DIST) {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_LEFT;
        } else {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_LEFT;
        }
    } else if (curr_distances[4] < MAX_DIST) {
        if (curr_distances[5] < MAX_DIST) {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        } else {
            left_turn_ratio = 1;
            right_turn_ratio = 1;
            return ADJUST_RIGHT;
        }
    } else if (curr_distances[0] < MAX_DIST) {
        return SEARCH_LEFT;
    } else if (curr_distances[5] < MAX_DIST) {
        return SEARCH_RIGHT;
    } else if (lastState == WAIT_FOR_START) {
        return STARTUP;
    }

}

void drive(int left, int right, bool left_reverse, bool right_reverse) {
    left = left*left_multi*left_turn_ratio;
    right = right*right_multi*right_turn_ratio;
    uint8_t bytes[3];
    bytes[0] = ESC_ADDRESS;
    bytes[1] = right_reverse; //0 is drive forward
    bytes[2] = right;
    uint32_t crc = 0;
    for(int i = 0; i < 3; i++) {
        crc = crc ^ (bytes[i] << 8);
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
    }
    ESC_R_SERIAL.write(bytes[0]);
    ESC_R_SERIAL.write(bytes[1]);
    ESC_R_SERIAL.write(bytes[2]);
    ESC_R_SERIAL.write(((crc >> 8) & 0xFF));
    ESC_R_SERIAL.write((crc & 0xFF));

    bytes[0] = ESC_ADDRESS;
    bytes[1] = left_reverse; //0 is drive forward
    bytes[2] = left;
    crc = 0;
    for(int i = 0; i < 3; i++) {
        crc = crc ^ (bytes[i] << 8);
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc = crc << 1;
            }
        }
    }
    ESC_L_SERIAL.write(bytes[0]);
    ESC_L_SERIAL.write(bytes[1]);
    ESC_L_SERIAL.write(bytes[2]);
    ESC_L_SERIAL.write(((crc >> 8) & 0xFF));
    ESC_L_SERIAL.write((crc & 0xFF));
}

/**
 * INTERRUPT METHODS
**/
void do_line_action_left() {
    //TODO: implement
    //drive(x, y, true, true);
}
void do_line_action_right() {
    //TODO: implement
    //drive(y, x, true, true);
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
    icm.begin();
    icm.disableDataReadyInterrupt();
    icm.configAccel(ICM20948::ACCEL_RANGE_2G, ICM20948::ACCEL_DLPF_BANDWIDTH_6HZ);
    icm.configGyro(ICM20948::GYRO_RANGE_250DPS, ICM20948::GYRO_DLPF_BANDWIDTH_6HZ);
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

    Wire.setClock(100000);
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

    digitalWrite(0, HIGH);
    tof_left.init(1);
    tof_left.setAddress(0x30);
    tof_left.setTimeout(1000);
    delay(100);
    digitalWrite(1, HIGH);
    tof_left_45.init(1);
    tof_left_45.setAddress(0x32);
    tof_left_45.setTimeout(1000);
    delay(100);
    digitalWrite(2, HIGH);
    tof_left_center.init(1);    
    tof_left_center.setAddress(0x33);
    tof_left_center.setTimeout(1000);
    delay(100);
    digitalWrite(30, HIGH);
    tof_right_center.init(1);
    tof_right_center.setAddress(0x34);
    tof_right_center.setTimeout(1000); 
    delay(100);
    digitalWrite(31, HIGH);
    tof_right_45.init(1);
    tof_right_45.setAddress(0x35);
    tof_right_45.setTimeout(1000);
    delay(100);
    digitalWrite(32, HIGH);
    tof_right.init(1);
    tof_right.setAddress(0x29);
    tof_right.setTimeout(1000);

    tof_left.startContinuous(10);
    tof_left_45.startContinuous(10);
    tof_left_center.startContinuous(10);
    tof_right_center.startContinuous(10);
    tof_right_45.startContinuous(10);
    tof_right.startContinuous(10);
 }

 void setup_current() {
    pinMode(LEFT_CURRENT, INPUT);
    percent_overloaded_left = 0;
    check_overload = 0;
 }

 void setup_motors(){
    left_multi = 1;
    right_multi = 1;
    left_turn_ratio = 1;
    right_turn_ratio = 1;
    ESC_L_SERIAL.begin(115200);
    ESC_L_SERIAL.setRX(22);
    ESC_L_SERIAL.setTX(26);
    ESC_R_SERIAL.begin(115200);
    ESC_R_SERIAL.setRX(7);
    ESC_R_SERIAL.setTX(8);
 }

/**
 * SENSOR READ METHODS
**/
void get_accel() {
//    x_accel.add(icm.getAccelX_mss());
//    y_accel.add(icm.getAccelY_mss());
}
void get_gyro() {
    //TODO: implement?
}
void get_distances() {
    dist[0] = tof_left.readRangeContinuousMillimeters();
//    Serial.println("left ");
    Serial.println(dist[0]);
    dist[1] = tof_left_45.readRangeContinuousMillimeters();
    Serial.println(dist[1]);
    dist[2] = tof_left_center.readRangeContinuousMillimeters();
    Serial.println(dist[2]);
    dist[3] = tof_right_center.readRangeContinuousMillimeters();
    Serial.println(dist[3]);
    dist[4] = tof_right_45.readRangeContinuousMillimeters();
    Serial.println(dist[4]);
    dist[5] = tof_right.readRangeContinuousMillimeters();
    Serial.println(dist[5]);
    //distances.add(dist);
}

void get_current() {
    int time_at_current = curr_time - last_read_current;
    last_read_current = curr_time;
    int current = analogRead(LEFT_CURRENT)*voltage_to_current; //read in voltage then change to current using magic number
    total_currentxtime_left += time_at_current*current; //Keep track of current*time over the interval to average later
    current = analogRead(RIGHT_CURRENT)*voltage_to_current;
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
