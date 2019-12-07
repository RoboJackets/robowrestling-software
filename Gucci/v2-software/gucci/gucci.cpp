#include "gucci.h"

ICM20948 icm(Wire2, (uint8_t)0x68);

int dist[6];

volatile bool left_line_hit;
volatile bool right_line_hit;

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
volatile long right_encoder;
volatile long left_encoder;

double left_multi;
double right_multi;


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


State state_machine() {
    curr_time = micros();
    get_distances();
    get_current();
    if (percent_overloaded_left > 1 || percent_overloaded_right > 1) {
        return PANIC_FIRE;
    }
    if (curr_time - prev_time_accel > check_accel) {
        prev_time_accel = micros();
        get_accel();
        //if (y_acceleration > ouch || y_acceleration < -ouch) {
            // return PANIC_HIT;
        // }
    }

    Location curr_opponent_location = get_opponent();
    switch curr_opponent_location{
        case FRONT_CLOSE:
            return MEGA_SLAMMY_WHAMMY;

        case FRONT_FAR:
            return SLAMMY_WHAMMY;

        case LEFT_CORNER_FRONT:
            return ADJUST_1_LEFT;

        case RIGHT_CORNER_FRONT:
            return ADJUST_1_RIGHT;

        case LEFT_CORNER:
            return ADJUST_2_LEFT;

        case RIGHT_CORNER:
            return ADJUST_2_RIGHT;
        case LEFT_CORNER_SIDE:
            return ADJUST_3_LEFT;

        case RIGHT_CORNER_SIDE:
            return ADJUST_3_RIGHT;

        case LEFT_SIDE:
            return ADJUST_4_LEFT;

        case RIGHT_SIDE:
            return ADJUST_4_RIGHT;
    }
}

void drive(int left, int right, bool left_reverse, bool right_reverse) {
    left = left*left_multi;
    right = right*right_multi;
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
void left_on_line_int() {
    left_line_hit = true;
}
void right_on_line_int() {
    right_line_hit = true;
}

void left_off_line_int() {
    left_line_hit = false;
}
void right_off_line_int() {
    right_line_hit = false;
}

void increment_encoder_right() {
    if (digitalReadFast(RIGHT_B_ENCODER)) {
        right_encoder--;
    }
    else {
        right_encoder++;
    }
}

void increment_encoder_left() {
    if (digitalReadFast(LEFT_B_ENCODER)) {
        left_encoder++;
    }
    else {
        left_encoder--;
    }
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
    pinMode(IMU_ADDRESS_PIN, OUTPUT);
    digitalWrite(IMU_ADDRESS_PIN, LOW); //Don't ever set this high
    Wire2.begin();
    Wire2.setSDA(IMU_SDA);
    Wire2.setSCL(IMU_SCL);
    icm.begin();
    icm.disableDataReadyInterrupt();
    icm.configAccel(ICM20948::ACCEL_RANGE_2G, ICM20948::ACCEL_DLPF_BANDWIDTH_6HZ);
    icm.configGyro(ICM20948::GYRO_RANGE_250DPS, ICM20948::GYRO_DLPF_BANDWIDTH_6HZ);
 }

 void setup_distance() {
    /* tof setup */
    dist = {MAX_DIST, MAX_DIST, MAX_DIST, MAX_DIST, MAX_DIST, MAX_DIST};

    pinMode(TOF_L, OUTPUT);
    pinMode(TOF_L_45, OUTPUT);
    pinMode(TOF_L_C, OUTPUT);
    pinMode(TOF_R_C, OUTPUT);
    pinMode(TOF_R_45, OUTPUT);
    pinMode(TOF_R, OUTPUT);

    digitalWrite(TOF_L, LOW);
    digitalWrite(TOF_L_45, LOW);
    digitalWrite(TOF_L_C, LOW);
    digitalWrite(TOF_R_C, LOW);
    digitalWrite(TOF_R_45, LOW);
    digitalWrite(TOF_R, LOW);

    Wire.setClock(100000);
    Wire.begin();
    Wire.setSDA(A15);
    Wire.setSCL(A14);

    digitalWrite(TOF_L, HIGH);
    digitalWrite(TOF_L_45, HIGH);
    digitalWrite(TOF_L_C, HIGH);
    digitalWrite(TOF_R_C, HIGH);
    digitalWrite(TOF_R_45, HIGH);
    digitalWrite(TOF_R, HIGH);

    digitalWrite(TOF_L, LOW);
    digitalWrite(TOF_L_45, LOW);
    digitalWrite(TOF_L_C, LOW);
    digitalWrite(TOF_R_C, LOW);
    digitalWrite(TOF_R_45, LOW);
    digitalWrite(TOF_R, LOW);

    digitalWrite(TOF_R, HIGH);
    tof_left.init(1);
    tof_left.setAddress(0x30);
    tof_left.setTimeout(1000);
    delay(100);
    digitalWrite(TOF_R_45, HIGH);
    tof_left_45.init(1);
    tof_left_45.setAddress(0x32);
    tof_left_45.setTimeout(1000);
    delay(100);
    digitalWrite(TOF_R_C, HIGH);
    tof_left_center.init(1);
    tof_left_center.setAddress(0x33);
    tof_left_center.setTimeout(1000);
    delay(100);
    digitalWrite(TOF_L_C, HIGH);
    tof_right_center.init(1);
    tof_right_center.setAddress(0x34);
    tof_right_center.setTimeout(1000);
    delay(100);
    digitalWrite(TOF_L_45, HIGH);
    tof_right_45.init(1);
    tof_right_45.setAddress(0x35);
    tof_right_45.setTimeout(1000);
    delay(100);
    digitalWrite(TOF_L, HIGH);
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
    analogReadResolution(13);
    pinMode(LEFT_CURRENT, INPUT);
    pinMode(RIGHT_CURRENT, INPUT);
    percent_overloaded_left = 0;
    percent_overloaded_right = 0;
    check_overload = 0;
 }

 void setup_motors(){
    left_multi = 1;
    right_multi = 1;
    ESC_L_SERIAL.begin(115200);
    ESC_L_SERIAL.setRX(ESC_L_RX);
    ESC_L_SERIAL.setTX(ESC_L_TX);
    ESC_R_SERIAL.begin(115200);
    ESC_R_SERIAL.setRX(ESC_R_RX);
    ESC_R_SERIAL.setTX(ESC_R_TX);
 }

void setup_encoders(){
    pinMode(LEFT_A_ENCODER, INPUT);
    pinMode(RIGHT_A_ENCODER, INPUT);

    attachInterrupt(digitalPinToInterrupt(LEFT_A_ENCODER), increment_encoder_left, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_A_ENCODER), increment_encoder_right, RISING);
}

void setup_line(){
    pinMode(LEFT_REF_LINE, OUTPUT);
    analogWrite(LEFT_REF_LINE, LEFT_THRES_LINE);
    pinMode(RIGHT_REF_LINE, OUTPUT);
    analogWrite(RIGHT_REF_LINE, RIGHT_THRES_LINE);

    pinMode(LEFT_INT_LINE, INPUT);
    pinMode(RIGHT_INT_LINE, INPUT);

    attachInterrupt(digitalPinToInterrupt(LEFT_INT_LINE), left_line_int, FALLING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_INT_LINE), right_line_int, FALLING);
    attachInterrupt(digitalPinToInterrupt(LEFT_INT_LINE), left_line_int, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_INT_LINE), right_line_int, RISING);
}

void setup_remote(){
    pinMode(REMOTE_PIN, INPUT);
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
    dist[1] = tof_left_45.readRangeContinuousMillimeters();
    dist[2] = tof_left_center.readRangeContinuousMillimeters();
    dist[3] = tof_right_center.readRangeContinuousMillimeters();
    dist[4] = tof_right_45.readRangeContinuousMillimeters();
    dist[5] = tof_right.readRangeContinuousMillimeters();
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

Location get_opponent(){

    bool left_side_valid = DIST_LEFT_SIDE < MAX_DIST; //Is the distance on the sensor a resonable number
    bool left_corner_valid = DIST_LEFT_CORNER < MAX_DIST;
    bool left_front_valid = DIST_LEFT_CENTER < MAX_DIST;
    bool left_front_close_valid = DIST_LEFT_CENTER < CLOSE_DIST;
    bool right_front_close_valid = DIST_RIGHT_CENTER < CLOSE_DIST;
    bool right_front_valid = DIST_RIGHT_CENTER < MAX_DIST;
    bool right_corner_valid = DIST_RIGHT_CORNER < MAX_DIST;
    bool right_side_valid = DIST_RIGHT_SIDE < MAX_DIST;

    if((left_front_close_valid || right_front_close_valid)
        && !(right_corner_valid || left_corner_valid || left_side_valid || right_side_valid)){
        return FRONT_CLOSE;
    }

    if((left_front_valid || right_front_valid)
            && !(right_corner_valid || left_corner_valid || left_side_valid || right_side_valid)){
        return FRONT_FAR;
    }

    if(left_front_valid && left_corner_valid
            && !(right_corner_valid || right_front_valid || left_side_valid || right_side_valid)){
        return LEFT_CORNER_FRONT;
    }

    if(right_front_valid && right_corner_valid
            && !(left_corner_valid || left_front_valid || left_side_valid || right_side_valid)){
        return RIGHT_CORNER_FRONT;
    }

    if(left_corner_valid
            && !(right_corner_valid || right_front_valid || left_side_valid || right_side_valid || left_front_valid)){
        return LEFT_CORNER;
    }

    if(right_corner_valid
            && !(left_corner_valid || right_front_valid || left_side_valid || right_side_valid || left_front_valid)){
        return RIGHT_CORNER;
    }

    if(left_side_valid && left_corner_valid
            && !(right_corner_valid || right_front_valid || left_front_valid || right_side_valid)){
        return LEFT_CORNER_SIDE;
    }

    if(right_side_valid && right_corner_valid
            && !(left_corner_valid || left_front_valid || left_side_valid || right_front_valid)){
        return RIGHT_CORNER_SIDE;
    }

    if(left_side_valid
            && !(right_corner_valid || right_front_valid || left_corner_valid || right_side_valid || left_front_valid)){
        return LEFT_SIDE;
    }

    if(right_side_valid
            && !(left_corner_valid || right_front_valid || left_side_valid || right_corner_valid || left_front_valid)){
        return RIGHT_SIDE;
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
