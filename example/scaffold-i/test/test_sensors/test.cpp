#include "unity.h"
#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"

void setUp(void) { }
void tearDown(void) { }

/* asserts true is true */
void test_test(void) {
    TEST_ASSERT_TRUE(true);
}

void test_irsensor(void) {
    /* Checks Constructor */
    IRSensor* irSensor = new IRSensor();
    TEST_ASSERT_FALSE(irSensor->getValue());

    /* Checks Constructor Overload */
    irSensor = new IRSensor(true);
    TEST_ASSERT_TRUE(irSensor->getValue());

    /* Checks setValue(bool) function */
    irSensor->setValue(false);
    TEST_ASSERT_FALSE(irSensor->getValue());
    irSensor->setValue(true);
    TEST_ASSERT_TRUE(irSensor->getValue());
}

void test_linesensor(void) {
    /* Checks Constructor */
    LineSensor* lineSensor = new LineSensor();
    TEST_ASSERT_FALSE(lineSensor->getValue());
    lineSensor->setValue(501);
    TEST_ASSERT_TRUE(lineSensor->getValue());
    lineSensor->setValue(499);
    TEST_ASSERT_FALSE(lineSensor->getValue());

    /* Checks Constructor Overload 1 */
    lineSensor = new LineSensor(true);
    TEST_ASSERT_TRUE(lineSensor->getValue());    
    lineSensor->setValue(499);
    TEST_ASSERT_FALSE(lineSensor->getValue());
    lineSensor->setValue(501);
    TEST_ASSERT_TRUE(lineSensor->getValue());

    /* Checks Constructor Overload 2 */
    lineSensor = new LineSensor(900);
    TEST_ASSERT_FALSE(lineSensor->getValue());    
    lineSensor->setValue(899);
    TEST_ASSERT_FALSE(lineSensor->getValue());
    lineSensor->setValue(901);
    TEST_ASSERT_TRUE(lineSensor->getValue());

    /* Checks Constructor Overload 3 */
    lineSensor = new LineSensor(true, 300);
    TEST_ASSERT_TRUE(lineSensor->getValue());    
    lineSensor->setValue(299);
    TEST_ASSERT_FALSE(lineSensor->getValue());
    lineSensor->setValue(301);
    TEST_ASSERT_TRUE(lineSensor->getValue());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_test);
    RUN_TEST(test_irsensor);
    RUN_TEST(test_linesensor);
    return UNITY_END();
}
