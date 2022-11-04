#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"

template<typename T>
class SlammyWhammy : public BT::SequenceNode<T> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : turnSpeed(turnSpeed), slamSpeed(slamSpeed), SequenceNode() {
        
    }

private:
    int turnSpeed;
    int slamSpeed;
};

#endif