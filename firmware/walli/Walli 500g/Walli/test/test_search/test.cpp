#include "unity.h"
#include "Sensors/IRSensor.h"
#include "Sensors/LineSensor.h"
void setUp(void) {

}

void tearDown(void){

}

void test_search(void) {
    TEST_ASSERT_TRUE(true);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_search);
    return UNITY_END();
}
