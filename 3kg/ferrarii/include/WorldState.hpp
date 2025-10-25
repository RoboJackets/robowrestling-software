#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "LineSensor.hpp"
#include "IRSensor.hpp"

enum SelfPositionEnum{NOT_ON_LINE, ON_LINE_TOP_LEFT, ON_LINE_TOP_RIGHT, ON_LINE_BOTTOM_LEFT, ON_LINE_BOTTOM_RIGHT};
enum OpponentPositionEnum{FRONT_CLOSE, FRONT_FAR, CLOSE_LEFT, MID_LEFT, FAR_LEFT, CLOSE_RIGHT, MID_RIGHT, FAR_RIGHT, BEHIND, NOT_SEEN};

class WorldState {
    private:
        OpponentPositionEnum lastPosition;
        LineSensor* LN_LF;
        LineSensor* LN_RF;
        LineSensor* LN_LB;
        LineSensor* LN_RB;
        IRSensor* IR_F;
        IRSensor* IR_30L;
        IRSensor* IR_60L;
        IRSensor* IR_90L;
        IRSensor* IR_30R;
        IRSensor* IR_60R;
        IRSensor* IR_90R;
        IRSensor* IR_B;
    public:
        WorldState(
            LineSensor* _LN_LF, 
            LineSensor* _LN_RF, 
            LineSensor* _LN_LB, 
            LineSensor* _LN_RB,
            IRSensor* _IR_F,
            IRSensor* _IR_30L,
            IRSensor* _IR_60L,
            IRSensor* _IR_90L,
            IRSensor* _IR_30R,
            IRSensor* _IR_60R,
            IRSensor* _IR_90R,
            IRSensor* _IR_B
        );
        SelfPositionEnum getOnLineStatus();
        OpponentPositionEnum getOpponentPosition();
        OpponentPositionEnum getLastOpponentPosition();
        void clearOpponentPosition();
};

#endif