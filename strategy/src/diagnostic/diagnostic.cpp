void checkMotor() {
    int InitRight = right_encoder;
    int InitLeft = left_encoder;
    drive(127,255);
    delay(5000);
    drive(0,0);
    double RightSpeed = right_encoder/(4096*5);
    double LeftSpeed = left_encoder/(4096*5);

}