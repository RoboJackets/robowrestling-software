#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"

template<typename T, typename U>
class SlammyWhammy : public BT::SequenceNode<T, U> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : turnSpeed(turnSpeed), slamSpeed(slamSpeed), SequenceNode() {
        
    }

private:
    int turnSpeed;
    int slamSpeed;
};

#endif