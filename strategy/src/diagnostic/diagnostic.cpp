void check_motor() {
    int init_right = right_encoder;
    int init_left = left_encoder;
    drive(127,255);
    delay(5000);
    drive(0,0);
    double right_speed_f = (right_encoder-init_right)/(4096*5);
    double left_speed_f = (left_encoder-init_left)/(4096*5);
    init_right = right_encoder;
    init_left = left_encoder;
    drive(63,191);
    delay(5000);
    drive(0,0);
    double right_speed_r = (right_encoder-init_right)/(4096*5);
    double left_speed_r = (left_encoder-init_left)/(4096*5);
}