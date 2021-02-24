#include "gucci.h"


/* line sensor */
volatile bool line_hit;

/* distance sensors */
int dist[6];

/* imu variables */ 
ICM20948 imu(Wire, (uint8_t)0x69);
int curr_time; //Do we want to implement this
int prev_time_accel;
int accel[2];
int gyro_z;

/* motor power multipliers */
double left_multi;
double right_multi;

void drive(int left, int right) { //Values should be between 0-127
    bool left_reverse = left < 0;
    bool right_reverse = right < 0;
    left = abs(left);
    right = abs(right);
    
    left = left*left_multi;
    right = right*right_multi;
    uint8_t bytes[3];
    bytes[0] = ESC_ADDRESS;
    bytes[1] = !right_reverse; // the right one is reversed apparently 
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
void left_line_int() {
    line_hit = !digitalReadFast(LEFT_INT_LINE);
}
void right_line_int() {
    line_hit = !digitalReadFast(RIGHT_INT_LINE);
}

/* Method for startup action */
void do_startup_action() { 
    delay(5000);
}

/**
 * SETUP METHODS
**/
 void setup_imu() {
    Wire.begin();
    Wire.setSDA(IMU_SDA);
    Wire.setSCL(IMU_SCL);
    imu.begin();
    imu.disableDataReadyInterrupt();
    imu.configAccel(ICM20948::ACCEL_RANGE_2G, ICM20948::ACCEL_DLPF_BANDWIDTH_6HZ);
    imu.configGyro(ICM20948::GYRO_RANGE_250DPS, ICM20948::GYRO_DLPF_BANDWIDTH_6HZ);
 }

 void setup_distance() {
    LIDAR12_SERIAL.begin(115200);
    LIDAR12_SERIAL.setRX(LIDAR12_RX);
    LIDAR12_SERIAL.setTX(LIDAR12_TX);

    LIDAR34_SERIAL.begin(115200);
    LIDAR34_SERIAL.setRX(LIDAR34_RX);
    LIDAR34_SERIAL.setTX(LIDAR34_TX);

    LIDAR56_SERIAL.begin(115200);
    LIDAR56_SERIAL.setRX(LIDAR56_RX);
    LIDAR56_SERIAL.setTX(LIDAR56_TX);
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

void setup_line(){
    line_hit = 0;
    
    pinMode(LINE_REF, OUTPUT);
    analogWrite(LINE_REF, THRES_LINE);

    pinMode(LEFT_INT_LINE, INPUT);
    pinMode(RIGHT_INT_LINE, INPUT);

    attachInterrupt(digitalPinToInterrupt(LEFT_INT_LINE), left_line_int, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RIGHT_INT_LINE), right_line_int, CHANGE);
}

void setup_remote(){
    pinMode(REMOTE_PIN, INPUT);
}


/**
 * SENSOR READ METHODS
**/

bool get_line_flag() {
  return line_hit;
}

void get_accel() {
    imu.readSensor();
    accel[0] = imu.getAccelX_mss();
    accel[1] = imu.getAccelY_mss();
}

void get_gyro() {
    imu.readSensor();
    gyro_z = imu.getGyroZ_rads();
}

void get_distances() {
    digitalWrite(LIDAR12_MUX, LOW);
    dist[0] = read_lidar(LIDAR12_SERIAL);
    digitalWrite(LIDAR12_MUX, HIGH);
    dist[1] = read_lidar(LIDAR12_SERIAL);
    digitalWrite(LIDAR34_MUX, LOW);
    dist[2] = read_lidar(LIDAR34_SERIAL);
    digitalWrite(LIDAR34_MUX, HIGH);
    dist[3] = read_lidar(LIDAR34_SERIAL);
    digitalWrite(LIDAR56_MUX, LOW);
    dist[4] = read_lidar(LIDAR56_SERIAL);
    digitalWrite(LIDAR56_MUX, HIGH);
    dist[5] = read_lidar(LIDAR56_SERIAL);
}

int read_lidar(auto LIDAR) {
    int dist;
    byte byteArray [9];
    if (LIDAR) {
        LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
        dist = (byteArray[3] << 8) | (byteArray[2] << 0);
    }
    return dist;
}