#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"
#include "../../Behaviors/Search.h"
#include "../../Behaviors/Slam.h"

template<typename T, typename U>
class SlammyWhammy : public BT::SequenceNode<T, U> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : BT::SequenceNode<T,U>(0, 0) {
        search = new Search<T,U>(turnSpeed);
        this->AddNode(search);
        slam = new Slam<T,U>(slamSpeed);
        this->AddNode(slam);
    }

private:
    Search<T,U>* search;
    Slam<T,U>* slam;
};

#endif