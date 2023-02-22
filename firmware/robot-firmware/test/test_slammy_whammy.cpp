#include "unity.h"
#include "../src/Strategies/SlammyWhammy/SlammyWhammy.h"

struct inp {
    double lidars[6];
};

struct out {
    int motor1;
    int motor2;
};

SlammyWhammy<inp, out> strat(10, 20);

void test_slammy_whammy(void) {
    out res;
    res = strat.Run({1001, 1001, 1001, 1001, 1001, 1001});
    TEST_ASSERT_EQUAL(10, res.motor1);
    TEST_ASSERT_EQUAL(-10, res.motor2);

    res = strat.Run({5, 1001, 1001, 1001, 1001, 1001});
    TEST_ASSERT_EQUAL(-10, res.motor1);
    TEST_ASSERT_EQUAL(10, res.motor2);

    res = strat.Run({1001, 1001, 999, 999, 1001, 1001});
    TEST_ASSERT_EQUAL(-10, res.motor1);
    TEST_ASSERT_EQUAL(10, res.motor2);

    res = strat.Run({1001, 1001, 999, 999, 1001, 1001});
    TEST_ASSERT_EQUAL(20, res.motor1);
    TEST_ASSERT_EQUAL(20, res.motor2);

    res = strat.Run({1001, 1001, 1001, 1001, 1001, 1001});
    TEST_ASSERT_EQUAL(20, res.motor1);
    TEST_ASSERT_EQUAL(20, res.motor2);
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
