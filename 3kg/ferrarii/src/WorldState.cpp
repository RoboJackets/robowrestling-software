#include "WorldState.hpp"

WorldState::WorldState(LineSensor* _LN_LF, LineSensor* _LN_RF, LineSensor* _LN_LB, LineSensor* _LN_RB, IRSensor* _IR_F, IRSensor* _IR_30L, IRSensor* _IR_60L, IRSensor* _IR_90L, IRSensor* _IR_30R, IRSensor* _IR_60R, IRSensor* _IR_90R, IRSensor* _IR_B) {
    LN_LF = _LN_LF;
    LN_RF = _LN_RF;
    LN_LB = _LN_LB;
    LN_RB = _LN_RB;
    IR_F = _IR_F;
    IR_30L = _IR_30L;
    IR_60L = _IR_60L;
    IR_90L = _IR_90L;
    IR_30R = _IR_30R;
    IR_60R = _IR_60R;
    IR_90R = _IR_90R;
    IR_B = _IR_B;
    lastPosition = NOT_SEEN;
}

SelfPositionEnum WorldState::getOnLineStatus() {
    if (LN_LF->getValue() == ON_LINE) {
        return ON_LINE_TOP_LEFT;
    }
    if (LN_RF->getValue() == ON_LINE) {
        return ON_LINE_TOP_RIGHT;
    }
    if (LN_LB->getValue() == ON_LINE) {
        return ON_LINE_BOTTOM_LEFT;
    }
    if (LN_RB->getValue() == ON_LINE) {
        return ON_LINE_BOTTOM_RIGHT;
    } 
    return NOT_ON_LINE;
}

OpponentPositionEnum WorldState::getOpponentPosition() {
    if (IR_F->getValue() == 1 &&  IR_30L->getValue() == 1 && IR_30L->getValue() == 1) {
        lastPosition = FRONT_CLOSE;
        return FRONT_CLOSE;
    }
    if (IR_F->getValue() == 1) {
        lastPosition = FRONT_FAR;
        return FRONT_FAR;
    }
    if (IR_30L->getValue() == 1) {
        lastPosition = CLOSE_LEFT;
        return CLOSE_LEFT;
    }
    if (IR_30R->getValue() == 1) {
        lastPosition = CLOSE_RIGHT;
        return CLOSE_RIGHT;
    }
    if (IR_60L->getValue() == 1) {
        lastPosition = MID_LEFT;
        return MID_LEFT;
    }
    if (IR_60R->getValue() == 1) {
        lastPosition = MID_RIGHT;
        return MID_RIGHT;
    }
    if (IR_90L->getValue() == 1) {
        lastPosition = FAR_LEFT;
        return FAR_LEFT;
    }
    if (IR_90R->getValue() == 1) {
        lastPosition = FAR_RIGHT;
        return FAR_RIGHT;
    }
    if (IR_B->getValue() == 1) {
        lastPosition = BEHIND;
        return BEHIND;
    }
    return NOT_SEEN;
}

OpponentPositionEnum WorldState::getLastOpponentPosition() {
    getOpponentPosition();
    return lastPosition;
}

void WorldState::clearOpponentPosition() {
    lastPosition = NOT_SEEN;
}