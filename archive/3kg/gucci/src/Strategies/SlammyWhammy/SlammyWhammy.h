#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H
#include "Behaviors/Nodes/SequenceNode.h"
#include "Behaviors/Nodes/Node.h"
#include "../../Behaviors/Search.h"
#include "../../Behaviors/Slam.h"
#include "../FigureEight/FigureEight.h"
#include <Arduino.h>

#define LOCKOUT_TIME 300

template<typename T, typename U>
class SlammyWhammy : public BT::Node<T, U> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed) : BT::Node<T,U>(0, 0) {
        search = new Search<T,U>(100);
        figureEight = new FigureEight<T,U>(75, 850); 
        slam = new Slam<T,U>(slamSpeed);
    }


    U Run(T state) {
        // U out; 
        // out.currentLeftMotorPow = 0; 
        // out.currentRightMotorPow = 0; 
        // if (state.lidars[2] > 150 || state.lidars[3] > 150) {
        //     return out; 
        // }

        if ((state.lidars[2] > 150 || state.lidars[3] > 150) && !(millis() - lockout < LOCKOUT_TIME)) {
            return search->Run(state);
        } else {
            lockout = millis(); 
        }

        return slam->Run(state); 
    }

private:
    Search<T,U>* search;
    Slam<T,U>* slam;
    FigureEight<T,U>* figureEight;
    unsigned int lockout = 0; 
};

#endif