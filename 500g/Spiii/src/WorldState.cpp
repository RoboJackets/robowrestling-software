#include "WorldState.hpp"

WorldState::WorldState(
    LineSensor *_L_LN,
    LineSensor *_R_LN,
    LineSensor *_B_LN,
    IRSensor *_IR_45L,
    IRSensor *_IR_45R,
    IRSensor *_IR_90L,
    IRSensor *_IR_90R,
    IRSensor *_IR_F
) {
    L_LN = _L_LN;
    R_LN = _R_LN;
    B_LN = _B_LN;
    IR_45L = _IR_45L;
    IR_45R = _IR_45R;
    IR_90L = _IR_90L;
    IR_90R = _IR_90R;
    IR_F = _IR_F;
}

OpponentPositionEnum WorldState::getEnemyPosition() {
    int f = IR_F->getValue();
    int l_45 = IR_45L->getValue();
    int l_90 = IR_90L->getValue();
    int r_45 = IR_45R->getValue();
    int r_90 = IR_90R->getValue();
    if (f && l_45 && r_45) {
        enemyPosition = OpponentPositionEnum::FRONT_CLOSE;
        return OpponentPositionEnum::FRONT_CLOSE;
    }
    if (f && l_45) {
        enemyPosition = OpponentPositionEnum::REALLY_CLOSE_LEFT;
        return OpponentPositionEnum::REALLY_CLOSE_LEFT;
    }
    if (f && r_45) {
        enemyPosition = OpponentPositionEnum::REALLY_CLOSE_RIGHT;
        return OpponentPositionEnum::REALLY_CLOSE_RIGHT;
    }
    if (f) {
        enemyPosition = OpponentPositionEnum::FRONT_FAR;
        return OpponentPositionEnum::FRONT_FAR;
    }
    if (l_45) {
        enemyPosition = OpponentPositionEnum::MID_LEFT;
        return OpponentPositionEnum::MID_LEFT;
    }
    if (r_45) {
        enemyPosition = OpponentPositionEnum::MID_RIGHT;
        return OpponentPositionEnum::MID_RIGHT;
    }
    if (l_90) {
        enemyPosition = OpponentPositionEnum::FAR_LEFT;
        return OpponentPositionEnum::FAR_LEFT;
    }
    if (r_90) {
        enemyPosition = OpponentPositionEnum::FAR_RIGHT;
        return OpponentPositionEnum::FAR_RIGHT;
    }
    return OpponentPositionEnum::NOT_SEEN;
}

SelfPositionEnum WorldState::getPosition() {
    int l = L_LN->getValue();
    int r = R_LN->getValue();
    int b = B_LN->getValue();
    if (l && r) {
        selfPosition = SelfPositionEnum::ON_LINE_BOTH;
        return SelfPositionEnum::ON_LINE_BOTH;
    }
    if (l) {
        selfPosition = SelfPositionEnum::ON_LINE_LEFT;
        return SelfPositionEnum::ON_LINE_LEFT;
    }
    if (r) {
        selfPosition = SelfPositionEnum::ON_LINE_RIGHT;
        return SelfPositionEnum::ON_LINE_RIGHT;
    }
    if (b) {
        selfPosition = SelfPositionEnum::ON_LINE_BOTTOM;
        return SelfPositionEnum::ON_LINE_BOTTOM;
    }
    return SelfPositionEnum::NOT_ON_LINE;
}