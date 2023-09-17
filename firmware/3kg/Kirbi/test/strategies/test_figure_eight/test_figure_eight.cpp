#include "unity.h"
#include "../src/Strategies/FigureEight/FigureEight.h"

struct RobotState {
    int currentLeftMotorPow; 
    int currentRightMotorPow; 
};

FigureEight<RobotState, RobotState> strat(20, 200); 

void test_figure_eight(void) {
    RobotState state{0,0}; 

    RobotState output = strat.Run(state); 
    TEST_ASSERT_EQUAL(0, output.currentRightMotorPow);
    TEST_ASSERT_EQUAL(20, output.currentLeftMotorPow);

    delay(210); 

    output = strat.Run(state); 
    TEST_ASSERT_EQUAL(20, output.currentRightMotorPow);
    TEST_ASSERT_EQUAL(0, output.currentLeftMotorPow);
    
}


void setup() {
    UNITY_BEGIN();
    SerialUSB.begin(115200);
}

void loop() {
    delay(1000);
    RUN_TEST(test_figure_eight);
    UNITY_END();
}
