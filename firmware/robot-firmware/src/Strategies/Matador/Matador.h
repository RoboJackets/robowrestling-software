#ifndef MATADOR_H
#define MATADOR_H
#include <Arduino.h>
#include "Behaviors/Nodes/SequenceNode.h"
#include "Behaviors/WaitUntilClose.h"
#include "Behaviors/Leave.h"
#include "Behaviors/Slam.h"

template<typename T>
class Matador : public BT::SequenceNode<T> {
    public:
        Matador() : BT::SequenceNode<T, U>(0, 0) {
            waitUntilClose = new WaitUntilClose<T, U>();
            leave = new Leave<T, U>(millis());
            slam = new Slam<T, U>(1);

            this -> AddNode(waitUntilClose);
            this -> AddNode(leave);
            this -> AddNode(slam);
        }

    private:
        WaitUntilClose<T, U>* waitUntilClose;
        Leave<T, U>* leave;
        Slam<T, U>* slam;
};

#endif
