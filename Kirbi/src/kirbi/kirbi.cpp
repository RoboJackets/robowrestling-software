#include "kirbi.h"

ICM20948 icm(Wire2, (uint8_t)0x68);

int dist[6];

volatile bool left_line_hit;
volatile bool right_line_hit;

/* acceleration timing variables */
int curr_time;
int prev_time_accel;
int check_accel;

/* encoder counts */
volatile int right_encoder;
volatile int left_encoder;

double left_multi;
double right_multi;


/* Current sensing stuff */
double r1 = 2.3;
double r2 = 7.28;
double nominal_current = 4.12;
const double precalc = 2.01873 //nominal_current*(sqrt(r1/(r1+r2)))
const double tw = 42.2;
int total_currentxtime_left;
int total_currentxtime_right;
double percent_overloaded_left;
double percent_overloaded_right;
int prev_time_current; //for use with curr_time
int last_read_current;
int check_overload;
const double voltage_to_current = .01611328;

/* configurations */
//lidar serial configs
byte configOutput [5] = {0x5A, 0x05, 0x07, 0x01, 0x11};
byte configUART [5] = {0x5A, 0x05, 0x0A, 0x00, 0x11};


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
     /* lidar setup */
     LEFT_LIDAR_SERIAL.begin(115200);
     LEFT_LIDAR_SERIAL.write(configUART, 5);
     LEFT_LIDAR_SERIAL.write(configOutput, 5);
     RIGHT_LIDAR_SERIAL.begin(115200);
     RIGHT_LIDAR_SERIAL.write(configUART, 5);
     RIGHT_LIDAR_SERIAL.write(configOutput, 5);
     pinMode(DIST_L, INPUT);
     pinMode(DIST_L_45, INPUT);
     pinMode(DIST_R, INPUT);
     pinMode(DIST_R_45, INPUT);
 }

 void setup_current() {
    pinMode(LEFT_CURRENT, INPUT);
    percent_overloaded = 0;
    check_current = 0;
 }

 void setup_motors(){
    left_multi = 1;
    right_multi = 1;
    ESC_SERIAL.begin(115200);
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
    x_accel.add(icm.getAccelX_mss());
    y_accel.add(icm.getAccelY_mss());
}
void get_gyro() {
    //TODO: implement?
}
void get_distances() {
    int[] dist = int[6];
    dist[0] = digitalRead(DIST_L);
    dist[1] = digitalRead(DIST_L_45);
    dist[2] = read_lidar(LEFT_LIDAR_SERIAL);
    dist[3] = read_lidar(RIGHT_LIDAR_SERIAL);
    dist[4] = digitalRead(DIST_R_45);
    dist[5] = digitalRead(DIST_R);
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

Location get_opponent(){

    bool left_side_valid = DIST_LEFT_SIDE == 1; //Is the distance on the sensor a resonable number
    bool left_corner_valid = DIST_LEFT_CORNER == 1;
    bool left_front_valid = DIST_LEFT_CENTER < MAX_DIST;
    bool left_front_close_valid = DIST_LEFT_CENTER < CLOSE_DIST;
    bool right_front_close_valid = DIST_RIGHT_CENTER < CLOSE_DIST;
    bool right_front_valid = DIST_RIGHT_CENTER < MAX_DIST;
    bool right_corner_valid = DIST_RIGHT_CORNER == 1;
    bool right_side_valid = DIST_RIGHT_SIDE == 1;

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
