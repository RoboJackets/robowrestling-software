/**  
 *   example implementation of test.cpp in
 *   test/
 *   ├─ test_tester/
 *   │  ├─ test.cpp
 */
#include "unity.h"
void setUp(void) {
}

void tearDown(void) {
}

//asserts true is true
void test_test(void) {
    TEST_ASSERT_TRUE(true);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_test);
    return UNITY_END();
}