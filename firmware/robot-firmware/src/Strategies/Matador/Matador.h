#ifndef MATADOR_H
#define MATADOR_H
#include "Behaviors/Nodes/SequenceNode.h"
#include "Behaviors/WaitUntilClose.h"

struct MatadorState {

};

template<typename T>
class Matador : public BT::SequenceNode<T> {
    public:
        Matador() : BT::SequenceNode() {
            WaitUntilClose<MatadorState, nullptr> first_node = WaitUntilClose();
        }
};

#endif
