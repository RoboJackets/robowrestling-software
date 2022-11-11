#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"
#include "../../Behaviors/Search.h"
#include "../../Behaviors/Slam.h"

template<typename T, typename U>
class SlammyWhammy : public BT::SequenceNode<T, U> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : SequenceNode() {
        Search<T,U> search(turnSpeed);
        AddNode(search);
        Slam<T,U> slam(slam);
        AddNode(slam);
    }
};

#endif