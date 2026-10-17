#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "IRSensor.hpp"
#include "LineSensor.hpp"

enum SelfPositionEnum {NOT_ON_LINE, ON_LINE_BOTH, ON_LINE_LEFT, ON_LINE_RIGHT, ON_LINE_BOTTOM};
enum OpponentPositionEnum {FRONT_CLOSE, FRONT_FAR, REALLY_CLOSE_LEFT, REALLY_CLOSE_RIGHT, MID_LEFT, FAR_LEFT, MID_RIGHT, FAR_RIGHT, NOT_SEEN};

class WorldState {
private:
    LineSensor *L_LN;
    LineSensor *R_LN;
    LineSensor *B_LN;
    IRSensor *IR_45L;
    IRSensor *IR_45R;
    IRSensor *IR_90L;
    IRSensor *IR_90R;
    IRSensor *IR_F;

    OpponentPositionEnum enemyPosition;
    SelfPositionEnum selfPosition;
public:
    WorldState(
        LineSensor *_L_LN,
        LineSensor *_R_LN,
        LineSensor *_B_LN,
        IRSensor *_IR_45L,
        IRSensor *_IR_45R,
        IRSensor *_IR_90L,
        IRSensor *_IR_90R,
        IRSensor *_IR_F
    );
    OpponentPositionEnum getEnemyPosition();
    SelfPositionEnum getPosition();
};

#endif