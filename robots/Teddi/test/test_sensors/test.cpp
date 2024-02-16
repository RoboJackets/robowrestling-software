#include "unity.h"
#include "Sensors/IRSensor.h"
#include "Sensors/LineSensor.h"
#include <stdbool.h>

//IRSensor irSensor = IRSensor();


LineSensor lineSensor = LineSensor();
void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    TEST_ASSERT_TRUE(true);
}

void test_IRSensor_set(void) {
    IRSensor irSensor = IRSensor();
    irSensor.setLeftIRSensor(0);
    TEST_ASSERT_EQUAL_INT(0, irSensor.getLeftIRSensor());
    irSensor.setRightIRSensor(100);
    TEST_ASSERT_EQUAL_INT(100, irSensor.getRightIRSensor());
    irSensor.setMiddleIRSensor(1000);
    TEST_ASSERT_EQUAL_INT(1000, irSensor.getMiddleIRSensor());
}

void test_LineSensor_set(void) {
    LineSensor lineSensor = LineSensor();
    lineSensor.setLeftLineSensor(0);
    TEST_ASSERT_EQUAL_INT(0, lineSensor.getLeftLineSensor());
    lineSensor.setRightLineSensor(100);
    TEST_ASSERT_EQUAL_INT(100, lineSensor.getRightLineSensor());
    lineSensor.setBackLineSensor(1000);
    TEST_ASSERT_EQUAL_INT(1000, lineSensor.getBackLineSensor());
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_IRSensor_set);
    RUN_TEST(test_LineSensor_set);
    return UNITY_END();
}