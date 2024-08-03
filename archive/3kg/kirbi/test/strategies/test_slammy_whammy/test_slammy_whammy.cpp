#include "unity.h"
#include "../src/Strategies/SlammyWhammy/SlammyWhammy.h"

struct inp {
    double lidars[6];
    int currentLeftMotorPow = 0; 
    int currentRightMotorPow = 0;
};

struct out {
    int motor1;
    int motor2;
};

SlammyWhammy<inp, inp> strat(10, 20);

void test_slammy_whammy(void) {
    inp res;
    res = strat.Run({101, 101, 101, 101, 101, 101, 0, 0});
    TEST_ASSERT_EQUAL(10, res.currentLeftMotorPow);
    TEST_ASSERT_EQUAL(-10, res.currentRightMotorPow);

    res = strat.Run({101, 101, 99, 99, 101, 101});
    TEST_ASSERT_EQUAL(20, res.currentLeftMotorPow);
    TEST_ASSERT_EQUAL(20, res.currentRightMotorPow);

    res = strat.Run({101, 101, 101, 101, 101, 101});
    TEST_ASSERT_EQUAL(10, res.currentLeftMotorPow);
    TEST_ASSERT_EQUAL(-10, res.currentRightMotorPow);

    res = strat.Run({0xFFFF, 0xFFFF, 10, 10, 0xFFFF, 0xFFFF}); 
    TEST_ASSERT_EQUAL(20, res.currentLeftMotorPow); 
    TEST_ASSERT_EQUAL(20, res.currentRightMotorPow); 

}

void setup() {
    UNITY_BEGIN();
    SerialUSB.begin(115200);
}

void loop() {
    delay(1000);
    RUN_TEST(test_slammy_whammy);
    UNITY_END();
}
