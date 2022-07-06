#include <gtest/gtest.h> 
#include "simulator/sim.h" 


namespace {

TEST(SimTest, TestWindowDimensions) {

    /* Test Effective Zeros */
    EXPECT_EQ(EFFECTIVE_ZERO_X, LEFT_PANEL_WIDTH*vis_scale);
    EXPECT_EQ(EFFECTIVE_ZERO_Y, 0);

    /* Test Effective Dimensions */
    EXPECT_EQ(EFFECTIVE_WIDTH, WINDOW_WIDTH - EFFECTIVE_ZERO_X) << "EFFECTIVE_WIDTH value unexpected";
    EXPECT_EQ(EFFECTIVE_HEIGHT, WINDOW_HEIGHT - BOTTOM_PANEL_HEIGHT*vis_scale)  << "EFFECTIVE_HEIGHT value unexpected";

    /* Test Effective Center */
    EXPECT_EQ(EFFECTIVE_CENTER_X, (EFFECTIVE_WIDTH / 2) + EFFECTIVE_ZERO_X);
    EXPECT_EQ(EFFECTIVE_CENTER_Y, (EFFECTIVE_HEIGHT / 2));
}

TEST(SimTest, ConvertCMToPixel) {
    float cm = 5 * (dohyoRadius / (154.f / 2)); 

    EXPECT_FLOAT_EQ(cm, CMToPixel(5));
} 


}
