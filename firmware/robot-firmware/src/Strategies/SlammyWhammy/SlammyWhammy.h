#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"
#include "Behaviors/Nodes/Node.h"
#include "../../Behaviors/Search.h"
#include "../../Behaviors/Slam.h"

template<typename T, typename U>
class SlammyWhammy : public BT::Node<T, U> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : BT::Node<T,U>(0, 0) {
        search = new Search<T,U>(turnSpeed);
        slam = new Slam<T,U>(slamSpeed);
    }


    U Run(T state) {
        U out; 
        out.currentLeftMotorPow = 0; 
        out.currentRightMotorPow = 0; 
        if (state.lidars[2] > 100 || state.lidars[3] > 100) {
            return out; 
        }

        return slam->Run(state); 
    }

private:
    Search<T,U>* search;
    Slam<T,U>* slam;
};

#endif